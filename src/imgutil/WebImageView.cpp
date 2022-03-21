#include "WebImageView.h"

#include <QtGui/QDesktopServices>
#include <QNetworkReply>
#include <bb/cascades/Image>
#include <QNetworkConfigurationManager>
#include <QFile>
#include <QDir>
#include <QFileInfo>

using namespace bb::cascades;
using namespace bb::device;

MyQNetworkAccessManager * WebImageView::mNetManager = new MyQNetworkAccessManager();
QNetworkDiskCache * WebImageView::mNetworkDiskCache = new QNetworkDiskCache();
CellularRadioInfo * WebImageView::cellularRadioInfo = new CellularRadioInfo();
CellularNetworkInfo * WebImageView::cellularNetworkInfo = new CellularNetworkInfo();

WebImageView::WebImageView()
{
    // Creates the folder if it doesn't exv
    QFileInfo imageDir(QDir::homePath() + "/images/");
    if (!imageDir.exists()) {
        QDir().mkdir(imageDir.path());
    }

    // Initialize network cache
    //mNetworkDiskCache->setCacheDirectory(QDesktopServices::storageLocation(QDesktopServices::CacheLocation));

    // Set cache in manager
    //mNetManager->setCache(mNetworkDiskCache);

    // Set defaults
    mLoading = 0;
    mPostLoadingUrlLoaded = false;
}

const QVariantMap& WebImageView::url() const
{
    return mUrl;
}

const QVariantMap& WebImageView::postLoadingUrl() const
{
    return mPostLoadingUrl;
}

void WebImageView::setPostLoadingUrl(QVariantMap url)
{
    mPostLoadingUrl = url;
}

void WebImageView::loadImage(QUrl url, bool reset, bool forceUpdate)
{
    // Reset the image
    if (reset)
        resetImage();

    //If another URL was loading:
    //try {
    //    if(reply && reply != 0 && reply->isRunning()){
    //        disconnect(reply);
    //reply->abort();
    //    }
    //} catch(int e) {

    //}

    for (QVariantMap::const_iterator iter = mUrl.begin(); iter != mUrl.end(); ++iter) {
        qDebug() << iter.key() << iter.value();
    }

    QString mPostStr = ImageUtil::getImageFileNameFromUrl(mPostLoadingUrl.value("Path").toString());
    QString householderId = mUrl.value("Result").toMap().value("HouseholderId").toString();

    QString type = mUrl.value("Type").toString();
    QString pathStr = mUrl.value("URL").toMap().value("Path").toString();
    if (householderId.isEmpty()) {
        householderId = mUrl.value("HouseholderId").toString();
        if (type.isEmpty()) {
            type = "Householder";
        }
    }

    qDebug() << "saved mPostStr:" + mPostStr;
    qDebug()
            << "mUrl.value Household_LastName:"
                    + mUrl.value("Result").toMap().value("Household_LastName").toString();
    qDebug() << "mUrl.value HouseholderId:" << householderId;
    qDebug() << "mUrl.value Type:" << type;
    qDebug() << "mUrl.value pathStr:" << pathStr;
    QString urlStr = ImageUtil::getImageFileNameFromUrl(mUrl.value("Path").toString());
    qDebug() << "saved urlStr:" + urlStr;
    try { //Cehck if PostLoadingImage exists first - if yes, just load it
        if (!mPostStr.isEmpty() && !(urlStr == mPostStr)) {
            qDebug() << "!mPostStr.isEmpty() && !(urlStr == mPostStr)";
            QFileInfo imageFilePos(mPostStr);
            QFile imageFile(mPostStr);

            if (imageFile.exists()) {
                mPostLoadingUrlLoaded = true;
                loadFromFile(imageFilePos.filePath());
                qDebug() << "loadFromFile:" + imageFilePos.filePath();

                emit urlChanged();
                return;
            } else {
                QFile imageSdcardFile(ImageUtil::getSdcardImageFileNameFromUrl(mPostStr));
                if (imageSdcardFile.exists()) {
                    qDebug() << "loading image from file";
                    qDebug() << "imageFile.filePath():" + imageSdcardFile.fileName();
                    loadFromFile(imageSdcardFile.fileName());
                }
                qDebug() << "image file does not exist:" + imageFilePos.filePath();
            }

        }

        if (!url.isEmpty()) {
            qDebug() << "!url.isEmpty()";
            QString fileName = ImageUtil::getImageFileNameFromUrl(url.toString()); //"accounts/1000/appdata/com.ubtglobal.ConnectApplication.testDev_Application70a861f7/data/images/Householdersign.jpg"
            if (!householderId.isEmpty()) {
                fileName = ImageUtil::getImageFileNameFromUrl(type, householderId);
            }

            QFileInfo imageFile(fileName);
            QFile imageFileObj(fileName);
            qDebug() << "imageFile.absoluteFilePath:" + imageFile.absoluteFilePath();
            // If image doesn't exist, download it, otherwise reuse the image saved
            if (imageFileObj.exists()) {
                qDebug() << "loading image from file";
                qDebug() << "imageFile.filePath():" + imageFile.filePath();
                if(!loadFromFile(imageFile.filePath())) {
                    loadImageFromUrl(url.toString());
                }

            } else {
                QFile imageSdcardFile(ImageUtil::getSdcardImageFileNameFromUrl(fileName));
                if (imageSdcardFile.exists()) {
                    qDebug() << "loading image from file";
                    qDebug() << "imageFile.filePath():" + imageSdcardFile.fileName();
                    if(!loadFromFile(imageSdcardFile.fileName())) {
                        loadImageFromUrl(url.toString());
                    }
                } else {
                    // Create request
                    loadImageFromUrl(url.toString());
                }

            }

            emit urlChanged();
        }
    } catch (int e) {
        qDebug() << e;
    }
}
void WebImageView::loadImageFromUrl(QString url) {
    MyQNetworkRequest request(url, true);
    //request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);

    // Create reply
    //reply = mNetManager->get(request);
    QNetworkReply * reply = mNetManager->get(request);

    // Connect to signals
    QObject::connect(reply, SIGNAL(finished()), this, SLOT(imageLoaded()));
    QObject::connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this,
            SLOT(dowloadProgressed(qint64,qint64)));
}
void WebImageView::setUrl(QVariantMap url)
{
    // Variables
    mUrl = url;
    mLoading = 0;

    QUrl params;
    params.addQueryItem("bucket", mUrl.value("Bucket").toString());
    params.addQueryItem("path", mUrl.value("Path").toString());
    params.addQueryItem("type", mUrl.value("Type").toString());
    QString urlF = APIUtil::apiPhotosRedirect + "?" + params.encodedQuery();

    loadImage(urlF, true, false);
}

bool WebImageView::loadFromFile(QString filePath)
{
    QFile imageFile(filePath);
    if (imageFile.open(QIODevice::ReadOnly)) {
        QByteArray imageData1 = imageFile.readAll();
        /**
         * decrypt image
         */

        QString id = url().value("id").toString();
        QString localityId = url().value("localityId").toString();
        QString countryCode = url().value("countryCode").toString();
        QByteArray imageData = imageUtil.decrypt(imageData1, imageUtil.getHash(id, localityId, countryCode));

        if (imageData.isEmpty()) {
            return false;
        }

        qDebug() << "setting image data: file://" + filePath << " ======== " << id;
        setImage(Image(imageData));

        mLoading = 1;
        emit loadingChanged();

        if (!mPostLoadingUrl.isEmpty() && !mPostLoadingUrlLoaded) {
            QNetworkConfigurationManager mgr;
            QList<QNetworkConfiguration> activeConfigs = mgr.allConfigurations(
                    QNetworkConfiguration::Active);
            if (activeConfigs.count() > 0) {
                qDebug() << "Bearer names";
                foreach(const QNetworkConfiguration &net, activeConfigs){
                if (net.bearerType() == QNetworkConfiguration::BearerWLAN) {

                    mPostLoadingUrlLoaded = true;

                    QUrl params;
                    params.addQueryItem("bucket", mPostLoadingUrl.value("Bucket").toString());
                    params.addQueryItem("path", mPostLoadingUrl.value("Path").toString());
                    params.addQueryItem("type", mPostLoadingUrl.value("Type").toString());

                    QString urlF = APIUtil::apiPhotosRedirect + "?" + params.encodedQuery();

                    loadImage(urlF, false, true);

                    return true;
                }
            }

                qDebug() << "Has Internet connection, but not wifi - Testing if in roaming";

                if (!cellularNetworkInfo->isRoaming()) {
                    mPostLoadingUrlLoaded = true;

                    mPostLoadingUrlLoaded = true;

                    QUrl params;
                    params.addQueryItem("bucket", mPostLoadingUrl.value("Bucket").toString());
                    params.addQueryItem("path", mPostLoadingUrl.value("Path").toString());
                    params.addQueryItem("type", mPostLoadingUrl.value("Type").toString());

                    QString urlF = APIUtil::apiPhotosRedirect + "?" + params.encodedQuery();

                    loadImage(urlF, false, true);
                    return true;
                }
            } else {
                qDebug() << "No Wifi Internet connection";
            }
        }

    }
    return true;
}

double WebImageView::loading() const
{
    return mLoading;
}

void WebImageView::imageLoaded()
{
    // Get reply
    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());

    if (reply->error() == QNetworkReply::NoError) {
        if (isARedirectedUrl(reply)) {
            setURLToRedirectedUrl(reply);
            return;
        } else {
            QByteArray imageData = reply->readAll();

            if (ImageUtil::getImageFileNameFromUrl(url().value("Path").toString())
                    == ImageUtil::getImageFileNameFromUrl(reply->url().toString())
                    || ImageUtil::getImageFileNameFromUrl(postLoadingUrl().value("Path").toString())
                            == ImageUtil::getImageFileNameFromUrl(reply->url().toString())) {
                setImage(Image(imageData));
                QFile imageFile(ImageUtil::getImageFileNameFromUrl(reply->url().toString()));
                if (imageFile.open(QIODevice::WriteOnly)) {
                    imageFile.write(imageData);
                    imageFile.close();

                    QString id = url().value("id").toString();
                    QString localityId = url().value("localityId").toString();
                    QString countryCode = url().value("countryCode").toString();
                    imageUtil.encryptFile(imageFile.fileName(), imageUtil.getHash(id, localityId, countryCode));
                    //releaseSomeCache(MAX_NUMBER_OF_IMAGES_SAVED);
                }
            }
        }
    } else {
        qDebug() << reply->errorString();
        APIUtil::refreshToken();
    }


    if (!mPostLoadingUrl.isEmpty() && !mPostLoadingUrlLoaded) {
        mPostLoadingUrlLoaded = true;

        QUrl params;
        params.addQueryItem("bucket", mPostLoadingUrl.value("Bucket").toString());
        params.addQueryItem("path", mPostLoadingUrl.value("Path").toString());
        params.addQueryItem("type", mPostLoadingUrl.value("Type").toString());

        QString urlF = APIUtil::apiPhotosRedirect + "?" + params.encodedQuery();

        loadImage(urlF, false, true);
    }

    // Memory management
    reply->deleteLater();
}

bool WebImageView::isARedirectedUrl(QNetworkReply *reply)
{
    QUrl redirection = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
    return !redirection.isEmpty();
}

void WebImageView::setURLToRedirectedUrl(QNetworkReply *reply)
{
    QUrl redirectionUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
    QUrl baseUrl = reply->url();
    QUrl resolvedUrl = baseUrl.resolved(redirectionUrl);

    mLoading = 0;

    QVariantMap params;
    params["Path"] = resolvedUrl;
    params["id"] = url().value("id").toString();
    params["localityId"] = url().value("localityId").toString();
    params["countryCode"] = url().value("countryCode").toString();

    mUrl = params;

    loadImage(resolvedUrl.toString(), true, false);
}

void WebImageView::clearCache()
{
    mNetworkDiskCache->clear();

    QDir imageDir(QDir::homePath() + "/images");
    imageDir.setFilter(QDir::NoDotAndDotDot | QDir::Files);
    foreach(const QString& file, imageDir.entryList()){
    imageDir.remove(file);
}
}

void WebImageView::releaseSomeCache(const int& maxNumberOfImagesSaved)
{
    if (maxNumberOfImagesSaved < 0)
        return;

    QDir imageDir(QDir::homePath() + "/images");
    imageDir.setFilter(QDir::NoDotAndDotDot | QDir::Files);
    imageDir.setSorting(QDir::Time | QDir::Reversed);

    QStringList entryList = imageDir.entryList();
    for (int i = maxNumberOfImagesSaved; i < entryList.size(); i++) {
        imageDir.remove(entryList[i]);
    }
}

void WebImageView::dowloadProgressed(qint64 bytes, qint64 total)
{
    mLoading = double(bytes) / double(total);

    emit loadingChanged();
}


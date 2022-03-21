/*
 * Copyright (c) 2011-2015 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ConnectSyncControl.hpp"
#include "../database/SQLiteUtil.hpp"
#include "../api/APISyncHouseholdsRequest.hpp"
#include "../api/APILocalitiesRequest.hpp"
#include "../api/APISubdivisionsRequest.hpp"
#include "../api/APIInterchangesRequest.hpp"
#include "../api/APICountriesRequest.hpp"
#include "../api/APICountryConfigRequest.hpp"
#include <bb/system/SystemDialog>
#include <bb/system/SystemUiResult>
#include <bb/FileSystemInfo>
#include <QtCore/QFile>
#include <bb/Application>
#include <bb/data/JsonDataAccess>
#include <QCoreApplication>
#include <QTextCodec>
#include <QtCore/QTime>
#include <bb/cascades/Application>
#include <bb/cascades/Window>
#include <bb/cascades/ScreenIdleMode>
#include <bb/system/SystemToast>
#include <bb/system/SystemUiPosition>

using namespace bb::cascades;
using namespace bb::system;
using namespace bb::data;

#define QZP "ub1g3!#546t"
#define TEMP_FULLSYNC true

ConnectSyncControl::ConnectSyncControl(QObject *parent) :
                                                            QObject(parent),
                                                            replaceDb(false),
                                                            m_creatingDone(false),
                                                            m_householdDone(false),
                                                            m_localityDone(false),
                                                            m_subdivisionDone(false),
                                                            m_interchangeDone(false),
                                                            m_countryDone(false),
                                                            m_photoDone(false),
                                                            m_photoExtDone(false),
                                                            m_allDone(false)

{

}

bool ConnectSyncControl::creatingDone() const
{
    return m_creatingDone;
}

bool ConnectSyncControl::householdDone() const
{
    return m_householdDone;
}

bool ConnectSyncControl::localityDone() const
{
    return m_localityDone;
}

bool ConnectSyncControl::subdivisionDone() const
{
    return m_subdivisionDone;
}

bool ConnectSyncControl::interchangeDone() const
{
    return m_interchangeDone;
}

bool ConnectSyncControl::countryDone() const
{
    return m_countryDone;
}

bool ConnectSyncControl::photoDone() const
{
    return m_photoDone;
}

bool ConnectSyncControl::photoExtDone() const
{
    return m_photoExtDone;
}
bool ConnectSyncControl::allDone() const
{
    return m_allDone;
}
bool ConnectSyncControl::database() const
{
    return m_database;
}

void ConnectSyncControl::invoke()
{

    setScreenMode(0);

    qDebug() << "Hello Sync";

    //SQLiteUtil::setLastUpdated();
    //QString date = SQLiteUtil::getLastUpdated();

    SyncWorker *worker = new SyncWorker;
    worker->moveToThread(&workerThread);

    connect(&workerThread, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(this, SIGNAL(doRequestSync(const bool)), worker, SLOT(doSync(const bool)));
    connect(this, SIGNAL(doCancel()), worker, SLOT(cancelT()));
    connect(this, SIGNAL(doStart()), worker, SLOT(start()));
    connect(this, SIGNAL(doGetDatabase(const bool)), worker, SLOT(getDatabase(const bool)));

    connect(worker, SIGNAL(errorOcurred(QString)), this, SLOT(handleError(QString)));
    connect(worker, SIGNAL(requestlogin()), this, SLOT(handleLoginRequest()));

    connect(worker, SIGNAL(updateProgress(const int, const int)), this, SLOT(handleUpdateProgress(const int, const int)));
    connect(worker, SIGNAL(updateLog(const QString)), this, SLOT(handleUpdateLog(const QString)));
    connect(worker, SIGNAL(processDone(const int)), this, SLOT(handleDone(const int)));
    connect(worker, SIGNAL(syncPhotos()), this, SLOT(handleSyncPhotos()));
    connect(worker, SIGNAL(askUser()), this, SLOT(handleAskUser()));
    connect(worker, SIGNAL(downloadDatabase()), this, SLOT(handleDownloadDatabase()));

    workerThread.start();

    emit doRequestSync(replaceDb);

}

void ConnectSyncControl::showToast(QString message)
{
    SystemToast* m_toast = new SystemToast();

    m_toast->setBody(message);
    m_toast->setPosition(SystemUiPosition::MiddleCenter);
    m_toast->show();
}

void ConnectSyncControl::setSheet(Sheet *sheet) {
    mSheet = sheet;

}

void ConnectSyncControl::cancel()
{
    setScreenMode(1);

    emit doCancel();

    workerThread.blockSignals(true);
    workerThread.terminate();

    close();
}

void ConnectSyncControl::close()
{
    emit loadMainUser();
    mSheet->close();
}

void ConnectSyncControl::setHomeSource(AbstractPane *root)
{
    homeSource = root;
}

void ConnectSyncControl::setRoot(Page *root)
{
    rootSource = root;
    qDebug() << "Class: ConnectSyncControl.cpp";
    mProgressIndicator = rootSource->findChild<ProgressIndicator*>(QString("progressIndicator"));

}


void ConnectSyncControl::handleAskUser() {
    m_dialog = new SystemDialog("Proceed", "Cancel");

    m_dialog->setTitle("Do you wish to proceed?");

    m_dialog->setBody("The process will download around 1GB of data, make sure you are connect to a WIFI before proceeding...");


    // Connect the finished() signal to the
    // onDialogFinished() slot
    // The slot will check the SystemUiResult
    // to see which button was tapped

    bool success = connect(m_dialog,
            SIGNAL(finished(bb::system::SystemUiResult::Type)),
            this,
            SLOT(onDialogFinished(bb::system::SystemUiResult::Type)));

    if (success) {
        m_dialog->show();

    } else {
        m_dialog->deleteLater();
    }
}

void ConnectSyncControl::onDialogFinished(bb::system::SystemUiResult::Type type)
{
    if (type == SystemUiResult::ConfirmButtonSelection)
    {
        emit doGetDatabase(replaceDb);
    }
    else {
        qDebug() << "Dialog Rejected";
        // The user rejected the dialog
        m_dialog->deleteLater();

        cancel();
    }
}

void ConnectSyncControl::handleUpdateProgress(const int &total, const int &pos) {

    mSyncTotal = total;
    emit totalChanged();

    mSyncProgress = pos;
    emit progressChanged();

    //QString log = SQLiteUtil::getTypeDescription(res) + ": " + QString::number(reg) + "/" + QString::number(total);
    //qDebug() << log;
}

void ConnectSyncControl::handleUpdateLog(const QString &toLog) {

    qDebug() << toLog;
}



void ConnectSyncControl::handleError(const QString &error) {

}

void ConnectSyncControl::handleDone(const int &task)
{
    switch (task) {
        case 0:
            m_creatingDone = true;
            emit creatingDoneChanged();
            break;
        case 1:
            m_householdDone = true;
            emit householdDoneChanged();
            break;
        case 2:
            m_localityDone = true;
            emit localityDoneChanged();
            break;
        case 3:
            m_subdivisionDone = true;
            emit subdivisionDoneChanged();
            break;
        case 4:
            m_interchangeDone = true;
            emit interchangeDoneChanged();
            break;
        case 5:
            m_countryDone = true;
            emit countryDoneChanged();
            break;
        case 6:
            m_photoDone = true;
            emit photoDoneChanged();
            handleDone(8);
            break; //It's the last one, just keeping structure - call allDone when Photos are done
        case 8:
            m_allDone = true;
            emit allDoneChanged();
            setScreenMode(1);
        case 99:
            close();
            break;
    }

}

void ConnectSyncControl::handleDownloadDatabase() {

    QmlDocument *qml = QmlDocument::create("asset:///DetailScreens/SyncPhotosScreen.qml");
    CRUDResourceTable *lCRUDResourceTable = new CRUDResourceTable();

    //Expose sync control  to qml
    mDownloadManager = new DownloadManager(this);
    mDownloadManager->m_database = true;

    connect(mDownloadManager, SIGNAL(sdownloadingDone(const bool)), this, SLOT(downloadingDone(const bool)));
    //mDownloadManager->setHomeSource(rootSource);
    qml->setContextProperty("_manager", mDownloadManager);
    qml->setContextProperty("_control", this);

    Page *page = qml->createRootObject<Page>();
    //mDownloadManager->setRoot(page);

    pMySheet = Sheet::create().content(page).open();

    qml->setContextProperty("_sheet", mSheet);

    QUrl params;
    params.addQueryItem("bucket", "cb.ubtglobal.com");
    params.addQueryItem("path",  QString("Connect/app/database%1_alt.zip").arg(QString::number(DATABASE_VERSION)));
    params.addQueryItem("type", "CDN");

    QString url = APIUtil::apiPhotosRedirect + "?" + params.encodedQuery();

    mDownloadManager->downloadUrl(url);




}

void ConnectSyncControl::setScreenMode(int mode) {
    Window *winId = Application::instance()->mainWindow();
    switch(mode) {
        case 0:
            Application::instance()->mainWindow()->setScreenIdleMode(ScreenIdleMode::KeepAwake);
            if( winId != NULL )
            {
                int idleMode = SCREEN_IDLE_MODE_KEEP_AWAKE;
                screen_set_window_property_iv( screen_window_t(winId), SCREEN_PROPERTY_IDLE_MODE, &idleMode);
            }
            break;
        case 1:
            Application::instance()->mainWindow()->setScreenIdleMode(ScreenIdleMode::Normal);
            if( winId != NULL )
            {
                int idleMode = SCREEN_IDLE_MODE_NORMAL;
                screen_set_window_property_iv( screen_window_t(winId), SCREEN_PROPERTY_IDLE_MODE, &idleMode);
            }
            break;
    }

}

void ConnectSyncControl::handleLoginRequest() {

    QMetaObject::invokeMethod(homeSource, "openLogin");
}


void ConnectSyncControl::handleSyncPhotos() {

    if (AppSettings::getFirstPhotoDownload())
        imageDownloading();
    else {
        AppSettings::setImageDownloadPage(1);
        m_photoDone = true;
        emit photoDoneChanged();
        handleDone(8);
    }

}


int ConnectSyncControl::syncTotal() const
{
    return mSyncTotal;
}


int ConnectSyncControl::syncProgress() const
{
    return mSyncProgress;
}


bool ConnectSyncControl::extractFile(QString m_filename, bool images) {

    // Check if file exists
    QFile file(m_filename);
    if (!file.exists()){
        qDebug() << "File does not exist;"+m_filename;
        return false;
    }

    bool result = true;
    QuaZip *m_zip = new QuaZip(m_filename);

    QString dataFolder = QDir::currentPath();

    QString dest = dataFolder + "/data/";

    QDir dir(dest);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    qDebug() << "destination folder: " + dest;

    m_zip->open(QuaZip::mdUnzip);

    if (!m_zip) {
        return false;
    }

    QuaZipFile *currentFile = new QuaZipFile(m_zip);
    int entries = m_zip->getEntriesCount();
    int current = 0;

    for (bool more = m_zip->goToFirstFile(); more; more = m_zip->goToNextFile()) {
        ++current;
        // If the entry is a path ignore it
        // Path existence is ensured separately
        if (m_zip->getCurrentFileName().split("/").last() == "")
            continue;

        QString outfilename = dest + "/" + m_zip->getCurrentFileName();
        QFile outputFile(outfilename);
        // Make sure the output path exists
        if (!QDir().mkpath(QFileInfo(outfilename).absolutePath())) {
            result = false;
            qDebug() << "[ZipUtil] creating output path failed for:" << outfilename;
            break;
        }

        if (!outputFile.open(QFile::WriteOnly)) {
            result = false;
            qDebug() << "[ZipUtil] creating output file failed:" << outfilename;
            break;
        }

        if (images)
            currentFile->open(QIODevice::ReadOnly);
        else
            currentFile->open(QIODevice::ReadOnly, QZP);


        outputFile.write(currentFile->readAll());
        if (currentFile->getZipError() != UNZ_OK) {
            result = false;
            // Emit logItem(tr("Error during Zip operation"), LOGERROR);
            qDebug() << "[ZipUtil] QuaZip error:"
                    << currentFile->getZipError()
                    << "on file" << currentFile->getFileName();
            break;
        }
        currentFile->close();
        outputFile.close();
    }

    return result;

}

void ConnectSyncControl::imageDownloading() {

    QmlDocument *qml = QmlDocument::create("asset:///DetailScreens/SyncPhotosScreen.qml");
    CRUDResourceTable *lCRUDResourceTable = new CRUDResourceTable();

    //Expose sync control  to qml
    mDownloadManager = new DownloadManager(this);
    mDownloadManager->m_database = false;
    m_database = false;

    int total = (lCRUDResourceTable->getResourcesCount(ResourceType::Household, "", "", "")
            / APIUtil::pageSize);
    mDownloadManager->pagesTotal = total;
    mDownloadManager->pagesDownloaded = AppSettings::getImageDownloadPage();
    mDownloadManager->startStatus();


    connect(mDownloadManager, SIGNAL(sdownloadingDone(const bool)), this, SLOT(downloadingDone(const bool)));
    //mDownloadManager->setHomeSource(rootSource);
    qml->setContextProperty("_manager", mDownloadManager);
    qml->setContextProperty("_control", this);

    Page *page = qml->createRootObject<Page>();
    //mDownloadManager->setRoot(page);

    pMySheet = Sheet::create().content(page).open();

    qml->setContextProperty("_sheet", pMySheet);
    //currentPhotoPage = 1;
    currentPhotoPage = AppSettings::getImageDownloadPage();

    downloadPagedPhotos(currentPhotoPage);
}

void ConnectSyncControl::downloadingDone(const bool paged)
{
    if (paged) {
        AppSettings::setImageDownloadPage(currentPhotoPage++);
        downloadPagedPhotos(currentPhotoPage);
    } else {
        try {
            showToast("extracting Database...");
            extractDatabase();
        } catch (...) {
            showToast("Fatal exception extracting database.");
        }

        try {
            showToast("opening Database connection");
            if (SQLiteUtil::openConnection()) {

                handleDone(0);

                if (pMySheet)
                    pMySheet->close();

                doStart();
            }
        } catch (...) {
            showToast("Fatal exception opening database.");
        }
    }
}

void ConnectSyncControl::downloadPagedPhotos(int page) {
    CRUDResourceTable *lCRUDResourceTable = new CRUDResourceTable();


    QString response = lCRUDResourceTable->getResources(ResourceType::Household, "", "", "", page);

    JsonDataAccess dataAccess;
    QVariantMap m_householdModel = dataAccess.loadFromBuffer(response).toMap();

    // Parse the json response with JsonDataAccess
    const QVariantList searchResults = m_householdModel["Results"].toList();

    if (searchResults.size() <= 0) {
        handleDone(6);
        AppSettings::setFirstPhotoDownload(false);

        if (pMySheet)
            pMySheet->close();

        return;
    }


    foreach (const QVariant &artifact, searchResults) {
        QVariantMap artifactMap = artifact.toMap();

        QVariantMap photo340 = artifactMap.value("Photo").toMap().value("URL340").toMap();

        //Family Photo
        if (!photo340.value("Bucket").toString().isNull() && !photo340.value("Bucket").toString().isEmpty()) {
            QUrl params;
            params.addQueryItem("bucket", photo340.value("Bucket").toString());
            params.addQueryItem("path", photo340.value("Path").toString());
            params.addQueryItem("type", photo340.value("Type").toString());

            qDebug()<< "bucket:"+photo340.value("Bucket").toString();
            qDebug()<< "path:"+photo340.value("Path").toString();
            qDebug()<< "type:"+photo340.value("Type").toString();

            QString url = APIUtil::apiPhotosRedirect + "?" + params.encodedQuery();

            mDownloadManager->downloadUrl(url);
        }

        //HOUSEHOLDER AND SPOUSE PHOTOS
        QVariantMap householdPhoto = artifactMap.value("Householder").toMap().value("PhotoTag").toMap().value("URL").toMap();
        if (!householdPhoto.value("Bucket").toString().isNull() && !householdPhoto.value("Bucket").toString().isEmpty()) {
            QUrl params;
            params.addQueryItem("bucket", householdPhoto.value("Bucket").toString());
            params.addQueryItem("path", householdPhoto.value("Path").toString());
            params.addQueryItem("type", householdPhoto.value("Type").toString());

            QString url = APIUtil::apiPhotosRedirect + "?" + params.encodedQuery();

            mDownloadManager->downloadUrl(url);
        }


        QVariantMap spousePhoto = artifactMap.value("HouseholderSpouse").toMap().value("PhotoTag").toMap().value("URL").toMap();
        if (!spousePhoto.value("Bucket").toString().isNull() && !spousePhoto.value("Bucket").toString().isEmpty()) {
            QUrl params;
            params.addQueryItem("bucket", spousePhoto.value("Bucket").toString());
            params.addQueryItem("path", spousePhoto.value("Path").toString());
            params.addQueryItem("type", spousePhoto.value("Type").toString());

            QString url = APIUtil::apiPhotosRedirect + "?" + params.encodedQuery();

            mDownloadManager->downloadUrl(url);
        }



        //Family Members Photos
        const QVariantList familyMembers = artifactMap["FamilyMembers"].toList();
        foreach (const QVariant &member, familyMembers) {
            QVariantMap photoM = artifact.toMap().value("PhotoTag").toMap().value("URL").toMap();

            if (!photoM.value("Bucket").toString().isNull() && !photoM.value("Bucket").toString().isEmpty()) {
                QUrl params;
                params.addQueryItem("bucket", photoM.value("Bucket").toString());
                params.addQueryItem("path", photoM.value("Path").toString());
                params.addQueryItem("type", photoM.value("Type").toString());

                QString url = APIUtil::apiPhotosRedirect + "?" + params.encodedQuery();

                mDownloadManager->downloadUrl(url);
            }

        }


    }

    mDownloadManager->pagesDownloaded = page;


}


bool ConnectSyncControl::extractDatabase() {
    return extractFile(QString("./data/database%1_alt.zip").arg(QString::number(DATABASE_VERSION)), false);
}























//----------------------------------------------
//THREAD----------------------------------------
//---------------------------------------------

void SyncWorker::showToast(QString message)
{
    SystemToast* m_toast = new SystemToast();

    m_toast->setBody(message);
    m_toast->setPosition(SystemUiPosition::MiddleCenter);
    m_toast->show();
}

void SyncWorker::doSync(const bool &replaceDb)
{

    if (SQLiteUtil::initDatabase(replaceDb)) {
        qDebug() << "Database ready.";
        showToast("Database ready.");
    } else {
        qDebug() << "Error initiating Database";
        showToast("Error initiating Database");
    }

    qDebug() << "Hello Sync";

    m_householdQt = 0;
    m_householdPage = 1;
    m_localityQt = 0;
    m_localityPage = 1;
    m_subdivisionQt = 0;
    m_subdivisionPage = 1;
    m_interchangeQt = 0;
    m_interchangePage = 1;
    m_countryQt = 0;
    m_countryPage = 1;
    tempTotalRegs = 0;

    if (!APIUtil::isConnectedToInternet()) {
        showToast("No Wifi Internet connection");
        emit requestlogin();
        return;
    }

    getDatabase(replaceDb);

//    //ask to be connected to wifi.
//    QNetworkConfigurationManager mgr;
//    QList<QNetworkConfiguration> activeConfigs = mgr.allConfigurations(QNetworkConfiguration::Active);
//    if (activeConfigs.count() > 0){
//        qDebug() << "Bearer names";
//        foreach(const QNetworkConfiguration &net, activeConfigs) {
//            if (net.bearerType() == QNetworkConfiguration::BearerWLAN) {
//                getDatabase(replaceDb);
//                return;
//            }
//        }
//        emit askUser();
//        qDebug()<<"Has Internet connection, but not wifi";
//    }else {
//        qDebug()<<"No Wifi Internet connection";
//        //ask if want to proceed
//        emit askUser();
//    }

}
void SyncWorker::getDatabase(bool replaceDb) {

    if (!TEMP_FULLSYNC) {
        //IF REPLACE DB IS TRUE - JUST DOWNLOAD DATABASE - it's the first access
        if (replaceDb) {

            //request download database
            emit downloadDatabase();
            return;

        } else {

            if (SQLiteUtil::openConnection()) { //OTHERWISE, TRY TO OPEN DATABASE AND COMPARE VERSIONS

                bool ok = true;
                CRUDAboutTable mCRUDAboutTable;
                if (CRUDBase::databaseVersion() == mCRUDAboutTable.getVersion()) {
                    ok =  false;
                }
                SQLiteUtil::closeConnection();

                if (ok) { //If not the same version - download the database
                    emit downloadDatabase();
                    return;
                }

            }else { //if there was a problem openning the databse - download a new one as well
                emit downloadDatabase();
                return;
            }
        }
    }

    //IF EVERYTHING IS OK - START SYNC
    emit processDone(0);
    if (SQLiteUtil::openConnection()) {
        if (SQLiteUtil::databaseSetup()) {
            start();
            return;
        }
    }
}

void SyncWorker::start() {
    mCRUDAboutTable = new CRUDAboutTable();
    mCRUDSearchHouseholdTable = new CRUDSearchHouseholdTable();
    mCRUDResourceTable = new CRUDResourceTable();
    mCRUDSearchLocalityTable = new CRUDSearchLocalityTable();
    mCRUDSearchSubdivisionTable = new CRUDSearchSubdivisionTable();

    newerThan = mCRUDAboutTable->getLastUpdated();
    if (newerThan.isEmpty())
        newerThan = "0";

    requestHouseholdsActive(1);
}

void SyncWorker::cancelT() {

    QSqlDatabase database = QSqlDatabase::database();
    database.close();
}


void SyncWorker::requestHouseholds(int page)
{

    APISyncHouseholdsRequest* request = new APISyncHouseholdsRequest(this);
    bool ok = connect(request, SIGNAL(sigHouseholdsResponse(QString, bool)), this, SLOT(onRequestHouseholdsSyncResponse(QString, bool)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);

    //    qDebug() << "Request API: " + QTime::currentTime().toString("mm:ss.zzz");

    request->requestHouseholds(page, newerThan);

}

void SyncWorker::onRequestHouseholdsSyncResponse(const QString &info, bool success)
{

    //    qDebug() << "Response API: " + QTime::currentTime().toString("mm:ss.zzz");

    APISyncHouseholdsRequest *request = qobject_cast<APISyncHouseholdsRequest*>(sender());
    request->deleteLater();

    if (success) {

        if (info.trimmed().isEmpty())
            return;

        QVariantList m_householdModel;


        //parsing
        m_householdQt = 0;
        // Parse the json response with JsonDataAccess
        JsonDataAccess dataAccess;
        QVariantMap parsed = dataAccess.loadFromBuffer(info).toMap();
        m_householdQt = parsed.value("Total").toString().toInt();


        m_householdModel = parsed.value("Results").toList();




        if (m_householdQt > 0) {

            //Prepare next page
            m_householdPage++;
            requestHouseholds(m_householdPage);

            //update client
            int tempTotal = (m_householdQt / APIUtil::pageSyncSize);
            emit updateProgress(tempTotal, m_householdPage);

            //            qDebug() << "Request Household: " + QString::number(m_householdPage) + "/" + QString::number(tempTotal);
            //            qDebug() << "Saving to database - time: " + QTime::currentTime().toString("mm:ss.zzz");

            QList<QString> resourceIDs;
            QList<int> resourceTypes;
            QList<QString> resourceDescriptions;
            QList<QString> resourceAdDescriptions;
            QList<QString> resourceJsons;
            QList<QString> resourceThumbnailIds;
            QList<QString> resourceCountrys;
            QList<QString> resourceCountryNames;
            QList<int> resourceLocalitys;
            QList<QString> resourceLocalityNames;
            QList<int> resourceSubdivisions;
            QList<QString> resourceSubdivisionNames;

            //save to database
            foreach (const QVariant &artifact, m_householdModel) {
                //qDebug() << "Saving to database - Parsing - time: " + QTime::currentTime().toString("mm:ss.zzz");

                QString jsonBuffer;
                JsonDataAccess jda;
                jda.saveToBuffer(artifact, &jsonBuffer);

                //Maps
                QVariantMap household = artifact.toMap();
                QVariantMap householder = household.value("Householder").toMap();
                QVariantMap country = household.value("Country").toMap();
                QVariantMap householdLocality = household.value("Locality").toMap();
                QVariantMap subdivisionLocality = household.value("Subdivision").toMap();

                QVariantList familyMembers = household.value("FamilyMembers").toList();

                QString adDescription = "";
                foreach (const QVariant &member, familyMembers) {
                    QVariantMap mMember = member.toMap();

                    if (mMember.value("Householder").toMap().value("Id").toString() == household.value("HouseholderId").toString() &&
                            !(mMember.value("IsDeceased").toString() == "true")) {
                        if (!adDescription.isEmpty())
                            adDescription = adDescription + ", ";
                        adDescription = adDescription +  mMember.value("DisplayName").toString();
                    }
                }

                //qDebug() << "Saving to database - Finished Parsing - time: " + QTime::currentTime().toString("mm:ss.zzz");
                //qDebug() << "Saving to database - Delete - time: " + QTime::currentTime().toString("mm:ss.zzz");
                //delete previous
                mCRUDSearchHouseholdTable->deleteResource(household.value("HouseholderId").toString());
                //qDebug() << "Saving to database - Finished Delete - time: " + QTime::currentTime().toString("mm:ss.zzz");

                //qDebug() << "Saving to database - Add resource - time: " + QTime::currentTime().toString("mm:ss.zzz");

                resourceIDs.append(household.value("HouseholderId").toString());
                resourceTypes.append((int)ResourceType::Household);
                resourceDescriptions.append(household.value("LastName").toString() + ", " + household.value("FirstName").toString());
                resourceAdDescriptions.append(adDescription);
                resourceJsons.append(jsonBuffer);
                resourceThumbnailIds.append(household.value("Photo").toMap().value("SignedURL340").toString());
                resourceCountrys.append(country.value("Code").toString());
                resourceCountryNames.append(country.value("Name").toString());
                resourceLocalitys.append(householdLocality.value("Id").toInt());
                resourceLocalityNames.append(householdLocality.value("Name").toString());
                resourceSubdivisions.append(subdivisionLocality.value("Id").toInt());
                resourceSubdivisionNames.append(subdivisionLocality.value("Name").toString());
            }
            QList<int> ids = mCRUDResourceTable->insertOrUpdateBatch(resourceIDs, resourceTypes, resourceDescriptions,
                                                                       resourceAdDescriptions, resourceJsons, resourceThumbnailIds,
                                                                       resourceCountrys, resourceCountryNames, resourceLocalitys,
                                                                       resourceLocalityNames, resourceSubdivisions, resourceSubdivisionNames);


            //Search
            QList<QString> householdTableIDs;
            QList<QString> householdIDs;
            QList<QString> firstNames;
            QList<QString> firstNameReverseds;
            QList<QString> lastNames;
            QList<QString> lastNameReverseds;
            QList<QString> lastNameFirstNames;
            QList<QString> fullNames;
            QList<QString> fullNameReverseds;
            QList<QString> countryCodes;

            for (int index = 0; index < m_householdModel.size(); index++) {
                if (ids.at(index) <= 0)
                    continue;
                const QVariant &artifact = m_householdModel.at(index);
                QVariantMap household = artifact.toMap();
                QVariantMap country = household.value("Country").toMap();
                QVariantList familyMembers = household.value("FamilyMembers").toList();
                foreach (const QVariant &member, familyMembers) {
                    QVariantMap mMember = member.toMap();
                    if (mMember.value("Householder").toMap().value("Id").toString() == household.value("HouseholderId").toString()) {
                        householdTableIDs.append(QString::number(ids.at(index)));
                        householdIDs.append(household.value("HouseholderId").toString());
                        firstNames.append(mMember.value("FirstName").toString());
                        firstNameReverseds.append(SQLiteUtil::getReversed(mMember.value("FirstName").toString()));
                        lastNames.append(mMember.value("LastName").toString());
                        lastNameReverseds.append(SQLiteUtil::getReversed(mMember.value("LastName").toString()));
                        lastNameFirstNames.append(mMember.value("LastName").toString() + " " + mMember.value("FirstName").toString());
                        fullNames.append(mMember.value("FirstName").toString() + " " + mMember.value("LastName").toString());
                        fullNameReverseds.append(SQLiteUtil::getReversed(mMember.value("FirstName").toString() + " " +  mMember.value("LastName").toString()));
                        countryCodes.append(country.value("Code").toString());
                    }

                }
            }
            bool searchFlag = mCRUDSearchHouseholdTable->insertOrUpdateBatch(householdTableIDs, householdIDs, firstNames, firstNameReverseds,
                                                                            lastNames, lastNameReverseds, lastNameFirstNames,
                                                                            fullNames, fullNameReverseds, countryCodes);
            qDebug() << (searchFlag ? "Success" : "Failed");

            //save HOUSEHOLDER to search table
            householdTableIDs.clear();
            householdIDs.clear();
            firstNames.clear();
            firstNameReverseds.clear();
            lastNames.clear();
            lastNameReverseds.clear();
            lastNameFirstNames.clear();
            fullNames.clear();
            fullNameReverseds.clear();
            countryCodes.clear();
            for (int index = 0; index < m_householdModel.size(); index++) {
                if (ids.at(index) <= 0)
                    continue;
                const QVariant &artifact = m_householdModel.at(index);
                QVariantMap household = artifact.toMap();
                QVariantMap householder = household.value("Householder").toMap();
                QVariantMap country = household.value("Country").toMap();

                householdTableIDs.append(QString::number(ids.at(index)));
                householdIDs.append(household.value("HouseholderId").toString());
                firstNames.append(householder.value("FirstName").toString());
                firstNameReverseds.append(SQLiteUtil::getReversed(householder.value("FirstName").toString()));
                lastNames.append(householder.value("LastName").toString());
                lastNameReverseds.append(SQLiteUtil::getReversed(householder.value("LastName").toString()));
                lastNameFirstNames.append(householder.value("LastName").toString() + " " + householder.value("FirstName").toString());
                fullNames.append(householder.value("FirstName").toString() + " " + householder.value("LastName").toString());
                fullNameReverseds.append(SQLiteUtil::getReversed(householder.value("FirstName").toString() + " " +  householder.value("LastName").toString()));
                countryCodes.append(country.value("Code").toString());
            }
            bool houseHolderFlag = mCRUDSearchHouseholdTable->insertOrUpdateBatch(householdTableIDs, householdIDs, firstNames, firstNameReverseds,
                                                                                lastNames, lastNameReverseds, lastNameFirstNames,
                                                                                fullNames, fullNameReverseds, countryCodes);
            qDebug() << (houseHolderFlag ? "Success" : "Failed");

            //save HOUSEHOLDER SPOUSE to search table
            householdTableIDs.clear();
            householdIDs.clear();
            firstNames.clear();
            firstNameReverseds.clear();
            lastNames.clear();
            lastNameReverseds.clear();
            lastNameFirstNames.clear();
            fullNames.clear();
            fullNameReverseds.clear();
            countryCodes.clear();

            for (int index = 0; index < m_householdModel.size(); index++) {
                if (ids.at(index) <= 0)
                    continue;
                const QVariant &artifact = m_householdModel.at(index);
                QVariantMap household = artifact.toMap();
                QVariantMap householder = household.value("Householder").toMap();
                QVariantMap country = household.value("Country").toMap();
                QVariantMap householdSpouse = household.value("HouseholderSpouse").toMap();

                if (householdSpouse.size() > 0) {
                    householdTableIDs.append(QString::number(ids.at(index)));
                    householdIDs.append(household.value("HouseholderId").toString());
                    firstNames.append(householdSpouse.value("FirstName").toString());
                    firstNameReverseds.append(SQLiteUtil::getReversed(householdSpouse.value("FirstName").toString()));
                    lastNames.append(householdSpouse.value("LastName").toString());
                    lastNameReverseds.append(SQLiteUtil::getReversed(householdSpouse.value("LastName").toString()));
                    lastNameFirstNames.append(householdSpouse.value("LastName").toString() + " " + householdSpouse.value("FirstName").toString());
                    fullNames.append(householdSpouse.value("FirstName").toString() + " " + householdSpouse.value("LastName").toString());
                    fullNameReverseds.append(SQLiteUtil::getReversed(householdSpouse.value("FirstName").toString() + " " +  householdSpouse.value("LastName").toString()));
                    countryCodes.append(country.value("Code").toString());
                }

            }
            bool spouseFlag = mCRUDSearchHouseholdTable->insertOrUpdateBatch(householdTableIDs, householdIDs, firstNames, firstNameReverseds,
                                                                            lastNames, lastNameReverseds, lastNameFirstNames,
                                                                            fullNames, fullNameReverseds, countryCodes);
            qDebug() << (spouseFlag ? "Success" : "Failed");
            qDebug() << "saving to database page: " + QString::number(m_householdPage-1) + "  tot: " + QString::number((m_householdPage-1)*APIUtil::pageSyncSize) + "  regsSaved: " + QString::number(tempTotalRegs);
        }
        else {
            emit processDone(1);
            qDebug() << "HOUSEHOLD Finished:  page: " + QString::number(m_householdPage-1) + "  tot: " + QString::number((m_householdPage-1)*APIUtil::pageSyncSize) + "  regsSaved: " + QString::number(tempTotalRegs);

            requestLocalities(1);
        }

    } else if (info.compare("loginRequest") == 0) {

        //TODO - not logged
        qDebug() << " Error: not logged";
        emit processDone(99);

    } else {
        qDebug() << " Error: " + info;

        //emit processDone(1);

        requestHouseholds(m_householdPage); //retry
        //requestLocalities(1);

    }

}



void SyncWorker::requestHouseholdsActive(int page)
{

    APISyncHouseholdsRequest* request = new APISyncHouseholdsRequest(this);
    bool ok = connect(request, SIGNAL(sigHouseholdsActiveResponse(QString, bool)), this, SLOT(onRequestHouseholdsActiveSyncResponse(QString, bool)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);

    //    qDebug() << "Request HouseholdActiveSync API: " + QTime::currentTime().toString("mm:ss.zzz");

    request->requestHouseholdsActive(page, newerThan);

}

void SyncWorker::onRequestHouseholdsActiveSyncResponse(const QString &info, bool success)
{

    //    qDebug() << "Response API: " + QTime::currentTime().toString("mm:ss.zzz");

    APISyncHouseholdsRequest *request = qobject_cast<APISyncHouseholdsRequest*>(sender());
    request->deleteLater();

    if (success) {

        if (info.trimmed().isEmpty())
            return;

        QVariantList m_householdActiveModel;


        m_householdQt = 0;
        // Parse the json response with JsonDataAccess
        JsonDataAccess dataAccess;
        QVariantMap parsed = dataAccess.loadFromBuffer(info).toMap();

        m_householdActiveQt = parsed.value("Total").toString().toInt();
        m_householdActiveModel = parsed.value("Results").toList();

        if (m_householdActiveQt > 0) {


            int tempTotal = (m_householdActiveQt / APIUtil::pageSyncSize);
            emit updateProgress(tempTotal, m_householdActivePage);

            //            qDebug() << "Request Household Active: " + QString::number(m_householdPage) + "/" + QString::number(tempTotal);
            //            qDebug() << "Saving to database HA - time: " + QTime::currentTime().toString("mm:ss.zzz");

            int i = 0;
            //save to database
            foreach (const QVariant &artifact, m_householdActiveModel) {
                i++;

                QString memberId = artifact.toMap().value("MemberId").toString();
                QString householderId = artifact.toMap().value("HouseholderId").toString();

                mCRUDSearchHouseholdTable->deleteResource(householderId);
                mCRUDResourceTable->deleteResource(ResourceType::Household,householderId);

            }

            //Prepare next page
            m_householdActivePage++;
            requestHouseholdsActive(m_householdActivePage);

        }
        else {
            //emit processDone(1);

            requestHouseholds(1);

        }

    }else if (info.compare("loginRequest") == 0) {

        //TODO - not logged
        qDebug() << " Error: not logged";
        emit processDone(99);
    } else {
        qDebug() << " Error: " + info;


        requestHouseholds(1);

    }

}



void SyncWorker::requestLocalities(int page)
{


    APILocalitiesRequest* request = new APILocalitiesRequest(this);
    bool ok = connect(request, SIGNAL(sigLocalitiesResponse(QString, bool)), this, SLOT(onRequestLocalitiesSyncResponse(QString, bool)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);

    request->requestLocalities(page, "", newerThan);

}

void SyncWorker::onRequestLocalitiesSyncResponse(const QString &info, bool success)
{
    APILocalitiesRequest *request = qobject_cast<APILocalitiesRequest*>(sender());
    request->deleteLater();

    if (success) {

        if (info.trimmed().isEmpty())
            return;

        m_localityQt = 0;

        QVariantList m_Model;
        JsonDataAccess dataAccess;
        QVariantMap parsed = dataAccess.loadFromBuffer(info).toMap();
        m_localityQt = parsed.value("Total").toString().toInt();
        m_Model = parsed.value("Results").toList();

        if (m_localityQt > 0) {

            //update client
            //updateUi(ResourceType::Locality, (m_localityQt / APIUtil::pageSyncSize), m_localityPage);

            int tempTotal = (m_localityQt / APIUtil::pageSyncSize);
            updateProgress(tempTotal, m_localityPage);
            //Prepare next page
            m_localityPage++;
            requestLocalities(m_localityPage);

            QList<QString> resourceIDs;
            QList<int> resourceTypes;
            QList<QString> resourceDescriptions;
            QList<QString> resourceAdDescriptions;
            QList<QString> resourceJsons;
            QList<QString> resourceThumbnailIds;
            QList<QString> resourceCountrys;
            QList<QString> resourceCountryNames;
            QList<int> resourceLocalitys;
            QList<QString> resourceLocalityNames;
            QList<int> resourceSubdivisions;
            QList<QString> resourceSubdivisionNames;

            //save to database
            foreach (const QVariant &artifact, m_Model) {
                //delete previous
                mCRUDSearchLocalityTable->deleteResource(artifact.toMap().value("Id").toString());

                QString jsonBuffer;
                JsonDataAccess jda;
                jda.saveToBuffer(artifact, &jsonBuffer);

                resourceIDs.append(artifact.toMap().value("Id").toString());
                resourceTypes.append((int)ResourceType::Locality);
                resourceDescriptions.append(artifact.toMap().value("Name").toString());
                resourceAdDescriptions.append(artifact.toMap().value("Country").toMap().value("Name").toString());
                resourceJsons.append(jsonBuffer);
                resourceThumbnailIds.append(artifact.toMap().value("HallPhoto").toMap().value("SignedURL340").toString());
                resourceCountrys.append(artifact.toMap().value("Country").toMap().value("Code").toString());
                resourceCountryNames.append(artifact.toMap().value("Country").toMap().value("Name").toString());
                resourceLocalitys.append(0);
                resourceLocalityNames.append("");
                resourceSubdivisions.append(0);
                resourceSubdivisionNames.append("");
            }
            QList<int> ids = mCRUDResourceTable->insertOrUpdateBatch(resourceIDs, resourceTypes, resourceDescriptions,
                                                                   resourceAdDescriptions, resourceJsons, resourceThumbnailIds,
                                                                   resourceCountrys, resourceCountryNames, resourceLocalitys,
                                                                   resourceLocalityNames, resourceSubdivisions, resourceSubdivisionNames);

            //save it to search table
            QList<QString> localityTableIDs;
            QList<QString> localityIDs;
            QList<QString> names;
            QList<QString> countryCodes;
            for (int index = 0; index < m_Model.size(); index++) {
                if (ids.at(index) <= 0)
                    continue;
                const QVariant &artifact = m_Model.at(index);
                localityTableIDs.append(QString::number(ids.at(index)));
                localityIDs.append(artifact.toMap().value("Id").toString());
                names.append(artifact.toMap().value("Name").toString());
                countryCodes.append(artifact.toMap().value("Country").toMap().value("Code").toString());
            }
            bool localityFlag = mCRUDSearchLocalityTable->insertOrUpdateBatch(localityTableIDs, localityIDs, names, countryCodes);
            qDebug() << (localityFlag ? "Success" : "Failed");
        }else {
            emit processDone(2);
            requestSubdivisions(1);
        }

    }else if (info.compare("loginRequest") == 0) {

        //not logged
        qDebug() << " Error: not logged";
        emit processDone(99);

    } else {
        qDebug() << " Error: " + info;

        requestLocalities(m_localityPage);
    }


}



void SyncWorker::requestSubdivisions(int page)
{

    APISubdivisionsRequest* request = new APISubdivisionsRequest(this);
    bool ok = connect(request, SIGNAL(sigSubdivisionsResponse(QString, bool)), this, SLOT(onRequestSubdivisionsSyncResponse(QString, bool)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);

    request->requestSubdivisions(page, "", newerThan);

}

void SyncWorker::onRequestSubdivisionsSyncResponse(const QString &info, bool success)
{


    APISubdivisionsRequest *request = qobject_cast<APISubdivisionsRequest*>(sender());

    if (success) {

        if (info.trimmed().isEmpty())
            return;

        m_subdivisionQt = 0;

        QVariantList m_Model;
        JsonDataAccess dataAccess;
        QVariantMap parsed = dataAccess.loadFromBuffer(info).toMap();
        m_subdivisionQt = parsed.value("Total").toString().toInt();
        m_Model = parsed.value("Results").toList();




        if (m_subdivisionQt > 0) {

            //update client
            int tempTotal = (m_subdivisionQt / APIUtil::pageSyncSize);
            emit updateProgress(tempTotal, m_subdivisionPage);

            //Prepare next page
            m_subdivisionPage++;
            requestSubdivisions(m_subdivisionPage);

            QList<QString> resourceIDs;
            QList<int> resourceTypes;
            QList<QString> resourceDescriptions;
            QList<QString> resourceAdDescriptions;
            QList<QString> resourceJsons;
            QList<QString> resourceThumbnailIds;
            QList<QString> resourceCountrys;
            QList<QString> resourceCountryNames;
            QList<int> resourceLocalitys;
            QList<QString> resourceLocalityNames;
            QList<int> resourceSubdivisions;
            QList<QString> resourceSubdivisionNames;

            //save to database
            foreach (const QVariant &artifact, m_Model) {
                QString jsonBuffer;
                JsonDataAccess jda;
                jda.saveToBuffer(artifact, &jsonBuffer);

                resourceIDs.append(artifact.toMap().value("Id").toString());
                resourceTypes.append((int)ResourceType::Subdivision);
                resourceDescriptions.append(artifact.toMap().value("Name").toString());
                resourceAdDescriptions.append(artifact.toMap().value("Country").toMap().value("Name").toString());
                resourceJsons.append(jsonBuffer);
                resourceThumbnailIds.append(artifact.toMap().value("HallPhoto").toMap().value("SignedURL340").toString());
                resourceCountrys.append(artifact.toMap().value("Locality").toMap().value("Country").toMap().value("Code").toString());
                resourceCountryNames.append(artifact.toMap().value("Locality").toMap().value("Country").toMap().value("Name").toString());
                resourceLocalitys.append(artifact.toMap().value("Locality").toMap().value("Id").toInt());
                resourceLocalityNames.append(artifact.toMap().value("Locality").toMap().value("Name").toString());
                resourceSubdivisions.append(0);
                resourceSubdivisionNames.append("");
            }
            QList<int> ids = mCRUDResourceTable->insertOrUpdateBatch(resourceIDs, resourceTypes, resourceDescriptions,
                                                                   resourceAdDescriptions, resourceJsons, resourceThumbnailIds,
                                                                   resourceCountrys, resourceCountryNames, resourceLocalitys,
                                                                   resourceLocalityNames, resourceSubdivisions, resourceSubdivisionNames);


            //save it to search table
            QList<QString> subdivisionTableIDs;
            QList<QString> subdivisionIDs;
            QList<QString> names;
            QList<QString> countryCodes;
            for (int index = 0; index < m_Model.size(); index++) {
                if (ids.at(index) <= 0)
                    continue;
                const QVariant &artifact = m_Model.at(index);
                subdivisionTableIDs.append(QString::number(ids.at(index)));
                subdivisionIDs.append(artifact.toMap().value("Id").toString());
                names.append(artifact.toMap().value("Name").toString());
                countryCodes.append(artifact.toMap().value("Country").toMap().value("Code").toString());
            }
            bool subdivisionFlag = mCRUDSearchSubdivisionTable->insertOrUpdateBatch(subdivisionTableIDs, subdivisionIDs, names, countryCodes);
            qDebug() << (subdivisionFlag ? "Success" : "Failed");
        }else {
            emit processDone(3);

            requestInterchanges(1);
        }

    }else if (info.compare("loginRequest") == 0) {

        //not logged
        qDebug() << " Error: not logged";
        emit processDone(99);

    } else {
        qDebug() << " Error: " + info;

        //retry
        requestSubdivisions(m_subdivisionPage);
    }

    request->deleteLater();
}



void SyncWorker::requestInterchanges(int page)
{

    APIInterchangesRequest* request = new APIInterchangesRequest(this);
    bool ok = connect(request, SIGNAL(sigInterchangesResponse(QString, bool)), this, SLOT(onRequestInterchangesSyncResponse(QString, bool)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);

    request->requestInterchanges(page, "", newerThan);

}

void SyncWorker::onRequestInterchangesSyncResponse(const QString &info, bool success)
{


    APIInterchangesRequest *request = qobject_cast<APIInterchangesRequest*>(sender());
    request->deleteLater();

    if (success) {

        if (info.trimmed().isEmpty())
            return;

        m_interchangeQt = 0;

        QVariantList m_Model;
        JsonDataAccess dataAccess;
        QVariantMap parsed = dataAccess.loadFromBuffer(info).toMap();
        m_interchangeQt = parsed.value("Total").toString().toInt();
        m_Model = parsed.value("Results").toList();




        if (m_interchangeQt > 0) {

            //update client
            int tempTotal = (m_interchangeQt / APIUtil::pageSyncSize);
            emit updateProgress(tempTotal, m_interchangePage);

            QList<QString> resourceIDs;
            QList<int> resourceTypes;
            QList<QString> resourceDescriptions;
            QList<QString> resourceAdDescriptions;
            QList<QString> resourceJsons;
            QList<QString> resourceThumbnailIds;
            QList<QString> resourceCountrys;
            QList<QString> resourceCountryNames;
            QList<int> resourceLocalitys;
            QList<QString> resourceLocalityNames;
            QList<int> resourceSubdivisions;
            QList<QString> resourceSubdivisionNames;

            //save to database
            foreach (const QVariant &artifact, m_Model) {
                QString jsonBuffer;
                JsonDataAccess jda;
                jda.saveToBuffer(artifact, &jsonBuffer);

                resourceIDs.append(artifact.toMap().value("LocalityId").toString());
                resourceTypes.append((int)ResourceType::Interchange);
                resourceDescriptions.append(artifact.toMap().value("LocalityName").toString());
                resourceAdDescriptions.append(artifact.toMap().value("Distance").toString());
                resourceJsons.append(jsonBuffer);
                resourceThumbnailIds.append(ResourceType::Interchange + artifact.toMap().value("LocalityId").toString() + ".jpg");
                resourceCountrys.append(artifact.toMap().value("Country").toMap().value("Code").toString());
                resourceCountryNames.append(artifact.toMap().value("Country").toMap().value("Name").toString());
                resourceLocalitys.append(artifact.toMap().value("LocalityId").toInt());
                resourceLocalityNames.append("");
                resourceSubdivisions.append(0);
                resourceSubdivisionNames.append("");
            }
            QList<int> ids = mCRUDResourceTable->insertOrUpdateBatch(resourceIDs, resourceTypes, resourceDescriptions,
                                                   resourceAdDescriptions, resourceJsons, resourceThumbnailIds,
                                                   resourceCountrys, resourceCountryNames, resourceLocalitys,
                                                   resourceLocalityNames, resourceSubdivisions, resourceSubdivisionNames);
            qDebug() << "count: " + ids.size();

            //Prepare next page
            m_interchangePage++;
            requestInterchanges(m_interchangePage);

        }else {
            emit processDone(4);
            requestCountries(1);
        }

    }else if (info.compare("loginRequest") == 0) {

        //not logged
        qDebug() << " Error: not logged";
        emit processDone(99);

    } else {
        qDebug() << " Error: " + info;

        //retry
        requestInterchanges(m_interchangePage);
    }

}


void SyncWorker::requestCountries(int page)
{

    APICountriesRequest* request = new APICountriesRequest(this);
    bool ok = connect(request, SIGNAL(sigCountriesResponse(QString, bool)), this, SLOT(onRequestCountriesSyncResponse(QString, bool)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);

    request->reqCountries(page, false, newerThan);

}

void SyncWorker::onRequestCountriesSyncResponse(const QString &info, bool success)
{


    APICountriesRequest *request = qobject_cast<APICountriesRequest*>(sender());

    if (success) {

        if (info.trimmed().isEmpty())
            return;

        m_countryQt = 0;

        QVariantList m_Model;
        JsonDataAccess dataAccess;
        QVariantMap parsed = dataAccess.loadFromBuffer(info).toMap();
        m_countryQt = parsed.value("Total").toString().toInt();
        m_Model = parsed.value("Results").toList();

        if (m_countryQt > 0) {

            //update client
            int tempTotal = (m_countryQt / APIUtil::pageSyncSize);
            emit updateProgress(tempTotal, m_countryPage);

            //Prepare next page
            m_countryPage++;
            requestCountries(m_countryPage);

            QList<QString> resourceIDs;
            QList<int> resourceTypes;
            QList<QString> resourceDescriptions;
            QList<QString> resourceAdDescriptions;
            QList<QString> resourceJsons;
            QList<QString> resourceThumbnailIds;
            QList<QString> resourceCountrys;
            QList<QString> resourceCountryNames;
            QList<int> resourceLocalitys;
            QList<QString> resourceLocalityNames;
            QList<int> resourceSubdivisions;
            QList<QString> resourceSubdivisionNames;

            //save to database
            foreach (const QVariant &artifact, m_Model) {

                QString jsonBuffer;
                JsonDataAccess jda;
                jda.saveToBuffer(artifact, &jsonBuffer);

                resourceIDs.append(artifact.toMap().value("Code").toString());
                resourceTypes.append((int)ResourceType::Country);
                resourceDescriptions.append(artifact.toMap().value("Name").toString());
                resourceAdDescriptions.append(artifact.toMap().value("LocalitiesCount").toString() + " localities");
                resourceJsons.append(jsonBuffer);
                resourceThumbnailIds.append("");
                resourceCountrys.append(artifact.toMap().value("Code").toString());
                resourceCountryNames.append(artifact.toMap().value("Name").toString());
                resourceLocalitys.append(0);
                resourceLocalityNames.append("");
                resourceSubdivisions.append(0);
                resourceSubdivisionNames.append("");
            }
            QList<int> ids = mCRUDResourceTable->insertOrUpdateBatch(resourceIDs, resourceTypes, resourceDescriptions,
                                                                   resourceAdDescriptions, resourceJsons, resourceThumbnailIds,
                                                                   resourceCountrys, resourceCountryNames, resourceLocalitys,
                                                                   resourceLocalityNames, resourceSubdivisions, resourceSubdivisionNames);
            qDebug() << "count: " + ids.size();
        }else {
            //FINISHED
            emit processDone(5);

            mCRUDAboutTable->setLastUpdatedNow();
            AppSettings::setFirstAccess(false);

            AppSettings::setImageDownloadPage(1);
            emit processDone(6);

            //requestPhotos();

        }

    }else if (info.compare("loginRequest") == 0) {

        //not logged
        qDebug() << " Error: not logged";
        emit processDone(99);

    } else {
        qDebug() << " Error: " + info;

        //retry
        requestCountries(m_countryPage);


    }

    request->deleteLater();
}

//
void SyncWorker::requestPhotos()
{

    emit syncPhotos();
}


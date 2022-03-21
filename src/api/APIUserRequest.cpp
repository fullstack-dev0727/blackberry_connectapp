/*
 * Copyright UBT Global.
 *
 *  Created on: 16 Feb 2016
 *      Author: Lucas Bento
 */


#include "APIUserRequest.hpp"
#include <QtCore/QDateTime>

APIUserRequest::APIUserRequest(QObject *parent)
: QObject(parent)
{}

void APIUserRequest::requestCurrentUser()
{

    //check internet connection
    QNetworkConfigurationManager mgr;
    QList<QNetworkConfiguration> activeConfigs = mgr.allConfigurations(QNetworkConfiguration::Active);
    if (activeConfigs.count() > 0){
        qDebug()<<"Has Internet connection";

        MyQNetworkAccessManager* networkAccessManager = new MyQNetworkAccessManager(this);
        MyQNetworkRequest request(APIUtil::apiCurrentUserUrl + "?time=" +  QDateTime::currentMSecsSinceEpoch() , true);
        request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::AlwaysNetwork);

        QUrl params;

        QNetworkReply* reply =  networkAccessManager->get(request);


        bool ok = QObject::connect(reply, SIGNAL(finished()), this, SLOT(onCurrentUserReply()));

        Q_ASSERT(ok);
        Q_UNUSED(ok);


    }else {
        qDebug()<<"No Wifi Internet connection";

        //Request first from database
        QVariantMap *reg = mCRUDResourceTable.getResource(ResourceType::CurrentUser, "1");
        QString json = reg->value("resource_json").toString();

        if (!json.isEmpty())
            emit sigCurrentUserResponse(json, true);
        else
            emit sigCurrentUserResponse("Error getting user information.", false);
    }

}

void APIUserRequest::setDefaultLocality(QString defaulLocalityId, QString userId)
{
    MyQNetworkAccessManager* networkAccessManager = new MyQNetworkAccessManager(this);
    QString url = APIUtil::apiSetDefaultLocalityUrl;
    url = url.replace("{user}", userId);
    MyQNetworkRequest request(url, true);
    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::AlwaysNetwork);


    QVariant temp = defaulLocalityId;
    bb::data::JsonDataAccess jda;
    QByteArray postContent;
    jda.saveToBuffer(temp, &postContent);



    QNetworkReply* reply =  networkAccessManager->post(request, postContent);

    bool ok = QObject::connect(reply, SIGNAL(finished()), this, SLOT(onSetDefaultLocalityReply()));

    Q_ASSERT(ok);
    Q_UNUSED(ok);
}


void APIUserRequest::changeReq(QVariantMap changingRequest)
{
    //TODO - FINISH SENDING CHANGE REQUEST
    QString userId = AppSettings::getCurrentUserId();
    MyQNetworkAccessManager* networkAccessManager = new MyQNetworkAccessManager(this);
    QString url = APIUtil::apiChangeRequestUrl;
    url = url.replace("{user}", userId);
    MyQNetworkRequest request(url, true);
    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::AlwaysNetwork);


    bb::data::JsonDataAccess jda;
    QByteArray postContent;
    jda.saveToBuffer(changingRequest, &postContent);



    QNetworkReply* reply =  networkAccessManager->post(request, postContent);

    bool ok = QObject::connect(reply, SIGNAL(finished()), this, SLOT(onSendChangeRequestReply()));

    Q_ASSERT(ok);
    Q_UNUSED(ok);
}



void APIUserRequest::onCurrentUserReply()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QString response;
    bool success = false;
    if (reply) {
        qDebug() << "Testing - code: " + reply->errorString();

        if (reply->error() == QNetworkReply::NoError) {
            const int available = reply->bytesAvailable();
            if (available > 0) {

                const QByteArray buffer = reply->readAll();
                QString encoding = QString::fromAscii(reply->rawHeader("Content-Encoding"));
                bool gzipEncoding = encoding.contains("gzip");

                if (gzipEncoding) {
                    QByteArray decompressed;
                    if(QCompressor::gzipDecompress(buffer, decompressed))
                    {
                        response = QString::fromUtf8(decompressed);
                        success = true;
                    }
                    else {
                        response = tr("The request has failed. Check internet connection");
                        success = false;
                    }
                }else {
                    response = QString::fromUtf8(buffer);
                    success = true;
                }
            }

        } else if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 401) { //401 Unauthorized

            if (!requestCurrentUserRetry) {



                requestCurrentUserRetry = true;

                //Try to refresh token
                if (APIUtil::refreshToken()) {
                    QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this);
                    MyQNetworkRequest requestRetry(reply->request());
                    requestRetry.setupRequest(true);

                    QNetworkReply* replyRetry =  networkAccessManager->get(requestRetry);

                    bool ok = QObject::connect(replyRetry, SIGNAL(finished()), this, SLOT(onCurrentUserReply()));

                    Q_ASSERT(ok);
                    Q_UNUSED(ok);

                    return;

                }
            }

            //go to login page
            response = "loginRequest";
            success = false;
        }else {
            qDebug() << reply->errorString();
            const QByteArray buffer1 = reply->readAll();
            QString encoding = QString::fromAscii(reply->rawHeader("Content-Encoding"));
            bool gzipEncoding = encoding.contains("gzip");
            if (gzipEncoding) {
                QByteArray decompressed;
                if(QCompressor::gzipDecompress(buffer1, decompressed))
                    response = QString::fromUtf8(decompressed);
                else
                    response = tr("The request has failed. Check internet connection");
            }else
                response = QString::fromUtf8(buffer1);

        }



        reply->deleteLater();
    }

    if (response.trimmed().isEmpty() && !success) {
        response = tr("Request failed. Check internet connection");
    }


    //SAVE TO DATABASE
    if (success) {
        if (!response.isEmpty()) {
            mCRUDResourceTable.insertOrUpdate("1", ResourceType::CurrentUser, "", "", response, "", "", "", 0, "", 0, "");
        }
    }
    emit sigCurrentUserResponse(response, success);
}



void APIUserRequest::onSetDefaultLocalityReply()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QString response = "";
    bool success = false;
    if (reply) {
        if (reply->error() == QNetworkReply::NoError) {
            const int available = reply->bytesAvailable();
            if (available > 0) {
                const QByteArray buffer = reply->readAll();
                QString encoding = QString::fromAscii(reply->rawHeader("Content-Encoding"));
                bool gzipEncoding = encoding.contains("gzip");

                if (gzipEncoding) {
                    QByteArray decompressed;
                    if(QCompressor::gzipDecompress(buffer, decompressed))
                    {
                        response = QString::fromUtf8(decompressed);
                        success = false;
                    }
                    else {
                        response = tr("The request has failed. Check internet connection");
                        success = false;
                    }
                }else {
                    response = QString::fromUtf8(buffer);
                    success = false;
                }
            }else {
                //200 - no return = successful
                success = true;
            }

        } else if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 401) { //401 Unauthorized

            if (!requestSetDefaultLocalityRetry) {



                requestSetDefaultLocalityRetry = true;

                //Try to refresh token
                if (APIUtil::refreshToken()) {
                    QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this);
                    MyQNetworkRequest requestRetry(reply->request());
                    requestRetry.setupRequest(true);

                    QNetworkReply* replyRetry =  networkAccessManager->get(requestRetry);

                    bool ok = QObject::connect(replyRetry, SIGNAL(finished()), this, SLOT(onSetDefaultLocalityReply()));

                    Q_ASSERT(ok);
                    Q_UNUSED(ok);

                    return;

                }
            }

            //go to login page
            response = "loginRequest";
            success = false;
        }

        reply->deleteLater();
    }

    if (response.trimmed().isEmpty()) {
        response = tr("Request failed. Check internet connection");
    }

    emit sigSetDefaultLocalityResponse(response, success);
}

void APIUserRequest::onSendChangeRequestReply()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QString response;
    bool success = false;
    if (reply) {
        if (reply->error() == QNetworkReply::NoError) {
            const int available = reply->bytesAvailable();
            if (available > 0) {
                const QByteArray buffer = reply->readAll();
                QString encoding = QString::fromAscii(reply->rawHeader("Content-Encoding"));
                bool gzipEncoding = encoding.contains("gzip");

                if (gzipEncoding) {
                    QByteArray decompressed;
                    if(QCompressor::gzipDecompress(buffer, decompressed))
                    {
                        response = QString::fromUtf8(decompressed);
                        success = true;
                    }
                    else {
                        response = tr("The request has failed. Check internet connection");
                        success = false;
                    }
                }else {
                    response = QString::fromUtf8(buffer);
                    success = true;
                }
            }

        } else if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 401) { //401 Unauthorized

            if (!requestSetDefaultLocalityRetry) {



                requestSetDefaultLocalityRetry = true;

                //Try to refresh token
                if (APIUtil::refreshToken()) {
                    QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this);
                    MyQNetworkRequest requestRetry(reply->request());
                    requestRetry.setupRequest(true);

                    QNetworkReply* replyRetry =  networkAccessManager->get(requestRetry);

                    bool ok = QObject::connect(replyRetry, SIGNAL(finished()), this, SLOT(onSetDefaultLocalityReply()));

                    Q_ASSERT(ok);
                    Q_UNUSED(ok);

                    return;

                }
            }

            //go to login page
            response = "loginRequest";
            success = false;
        }

        reply->deleteLater();
    }

    if (response.trimmed().isEmpty()) {
        response = tr("Request failed. Check internet connection");
    }

    emit sigSendChangeResquestResponse(response, success);
}


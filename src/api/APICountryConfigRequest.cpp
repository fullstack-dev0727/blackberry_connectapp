/*
 * Copyright UBT Global.
 *
 *  Created on: 16 Feb 2016
 *      Author: Lucas Bento
 */


#include "APICountryConfigRequest.hpp"
#include <bb/data/JsonDataAccess>

using namespace bb::data;

APICountryConfigRequest::APICountryConfigRequest(QObject *parent)
: QObject(parent)
{}

/*
 * APICountryConfigRequest::requestCountryConfig
 * Request ConnectAPI the Country Config information
 */


void APICountryConfigRequest::requestCountryConfig()
{
    QString json;

    if (!AppSettings::getToken().isEmpty() && !AppSettings::getToken().isNull()) {
        //Request first from database
        QVariantMap *reg = mCRUDResourceTable.getResource(ResourceType::Country, AppSettings::getUserCountryCode()); //TODO - MAKE IT RIGHT
        json = reg->value("resource_json").toString();

        JsonDataAccess dataAccess;
        QVariantMap parsedResponse = dataAccess.loadFromBuffer(json).toMap();

        if (parsedResponse.value("ConnectConfig").toMap().value("TermsAndConditions").toString().isEmpty()) { //fallback to global config
            //Request first from database
            QVariantMap *reg1 = mCRUDResourceTable.getResource(ResourceType::Country, "ZZ");
            json = reg1->value("resource_json").toString();
        }
    }

    if (!json.isEmpty()) {
        emit sigCountryConfigResponse(json, true);
    }else {

        //Get My actual Country Id
        QString countryId = AppSettings::getUserCountryCode();
        if (countryId.isEmpty()) {
            countryId = "ZZ";
        }
        QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this);
        MyQNetworkRequest request(APIUtil::apiCountryConfigUrl + "/" + countryId + "/terms", true);

        QUrl params;

        QNetworkReply* reply =  networkAccessManager->get(request);

        bool ok = QObject::connect(reply, SIGNAL(finished()), this, SLOT(onCountryConfigReply()));

        Q_ASSERT(ok);
        Q_UNUSED(ok);
    }
}


void APICountryConfigRequest::onCountryConfigReply()
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

            if (!requestCountryConfigRetry) {

                requestCountryConfigRetry = true;

                //Try to refresh token
                if (APIUtil::refreshToken()) {
                    QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this);
                    MyQNetworkRequest requestRetry(reply->request());
                    requestRetry.setupRequest(true);

                    QNetworkReply* replyRetry =  networkAccessManager->get(requestRetry);

                    bool ok = QObject::connect(replyRetry, SIGNAL(finished()), this, SLOT(onCountryConfigReply()));

                    Q_ASSERT(ok);
                    Q_UNUSED(ok);

                    return;

                }

            }
            //go to login page
            response = "loginRequest";
            success = false;


        } else {
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

    if (response.trimmed().isEmpty()) {
        response = tr("Request failed. Check internet connection");
    }

    emit sigCountryConfigResponse(response, success);


}


/*
 * APICountryConfigRequest::requestCountryConfig
 * Sent to ConnectAPI the contact by Email
 */



void APICountryConfigRequest::sendCtcEmail(const QString &userId, const QString &subject, const QString &body)
{

    QString url = APIUtil::apiContactEmailUrl;
    if (!userId.isEmpty()) {
        url = APIUtil::apiUserSendMessageUrl;
        url.replace("{user}", userId);
    }

    QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this);
    MyQNetworkRequest request(url, true);



    QVariantMap postData;
    postData["Subject"] = subject;
    postData["Body"] = body;

    QVariant temp = QVariant(postData);

    bb::data::JsonDataAccess jda;

    QByteArray postContent;
    jda.saveToBuffer(temp, &postContent);



    QNetworkReply* reply =  networkAccessManager->post(request, postContent);


    bool ok = QObject::connect(reply, SIGNAL(finished()), this, SLOT(onContactEmailReply()));

    Q_ASSERT(ok);
    Q_UNUSED(ok);
}


void APICountryConfigRequest::onContactEmailReply()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QString response;
    bool success = false;
    if (reply) {
        if (reply->error() == QNetworkReply::NoError) {
            const int available = reply->bytesAvailable();
            if (available == 0) {
                success = true;
            }
        } else if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 401) { //401 Unauthorized

            if (!sendContactEmailRetry) {

                sendContactEmailRetry = true;

                //Try to refresh token
                if (APIUtil::refreshToken()) {
                    QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this);
                    MyQNetworkRequest requestRetry(reply->request());
                    requestRetry.setupRequest(true);

                    QNetworkReply* replyRetry =  networkAccessManager->get(requestRetry);

                    bool ok = QObject::connect(replyRetry, SIGNAL(finished()), this, SLOT(onContactEmailReply()));

                    Q_ASSERT(ok);
                    Q_UNUSED(ok);

                    return;

                }

            }
            //go to login page
            response = "loginRequest";
            success = false;


        } else {
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

    emit sigContactEmailResponse(response, success);
}

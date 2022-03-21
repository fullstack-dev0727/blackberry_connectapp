/*
 * Copyright UBT Global.
 *
 *  Created on: 04 Mar 2016
 *      Author: Lucas Bento
 */


#include "APIHouseholdsRequest.hpp"


APIHouseholdsRequest::APIHouseholdsRequest(QObject *parent)
: QObject(parent)
{}

/*
 * APIHouseholdsRequest::requestHouseholdsByLocality
 * Request to ConnectAPI the Households List
 */


void APIHouseholdsRequest::requestHouseholdsByLocality(int page, QString localityId)
{
    //Request first from datrabase
    QString json = mCRUDResourceTable.getResources(ResourceType::Household, localityId, "" , "",  page);

    if (!json.isEmpty()) {
        emit sigHouseholdsResponse(json, true);
    }else {

        QUrl params;
        params.addQueryItem("localityId", localityId);
        params.addQueryItem("itemsPerPage",  QString::number(APIUtil::pageSize));

        requestHouseholds(page, params);
    }
}

/*
 * APIHouseholdsRequest::requestHouseholdsBySubdivision
 * Request to ConnectAPI the Households List
 */


void APIHouseholdsRequest::requestHouseholdsBySubdivision(int page, QString subdivisionId)
{

    //Request first from datrabase
    QString json = mCRUDResourceTable.getResources(ResourceType::Household, "", subdivisionId , "",  page);

    if (!json.isEmpty()) {
        emit sigHouseholdsResponse(json, true);
    }else {

        QUrl params;
        params.addQueryItem("subdivisionId", subdivisionId);

        requestHouseholds(page, params);
    }
}

void APIHouseholdsRequest::requestHouseholds(int page, QUrl params)
{

    params.addQueryItem("page",  QString::number(page));
    params.addQueryItem("itemsPerPage",  QString::number(APIUtil::pageSize));
    params.addQueryItem("signPhotoUrls",  "false");

    QString url = APIUtil::apiHouseholdsUrl + "?" + params.encodedQuery();

    MyQNetworkAccessManager* networkAccessManager = new MyQNetworkAccessManager(this);
    MyQNetworkRequest request(url, true);

    QNetworkReply* reply =  networkAccessManager->get(request);

    bool ok = QObject::connect(reply, SIGNAL(finished()), this, SLOT(onHouseholdsReply()));

    Q_ASSERT(ok);
    Q_UNUSED(ok);

}

void APIHouseholdsRequest::requestHousehold(QString householdId)
{
    //Request first from datrabase
    QVariantMap *reg = mCRUDResourceTable.getResource(ResourceType::Household, householdId);
    QString json = reg->value("resource_json").toString();

    if (!json.isEmpty()) {
        emit sigHouseholdResponse(json, true);
    }else if (!reg->value("no_permission").toString().isEmpty()) {
        emit sigHouseholdResponse("no_permission", false);
    }else {

        QUrl params;
        params.addQueryItem("signPhotoUrls",  "false");

        QString url = APIUtil::apiHouseholdsUrl + "/" + householdId+ "?" + params.encodedQuery();

        MyQNetworkAccessManager* networkAccessManager = new MyQNetworkAccessManager(this);
        MyQNetworkRequest request(url, true);

        QNetworkReply* reply =  networkAccessManager->get(request);

        bool ok = QObject::connect(reply, SIGNAL(finished()), this, SLOT(onHouseholdReply()));

        Q_ASSERT(ok);
        Q_UNUSED(ok);
    }
}


void APIHouseholdsRequest::onHouseholdsReply()
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

            if (!requestHouseholdsRetry) {

                requestHouseholdsRetry = true;

                //Try to refresh token
                if (APIUtil::refreshToken()) {
                    QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this);
                    MyQNetworkRequest requestRetry(reply->request());
                    requestRetry.setupRequest(true);

                    QNetworkReply* replyRetry =  networkAccessManager->get(requestRetry);

                    bool ok = QObject::connect(replyRetry, SIGNAL(finished()), this, SLOT(onHouseholdsReply()));

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

    emit sigHouseholdsResponse(response, success);

}

void APIHouseholdsRequest::onHouseholdReply()
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

            if (!requestHouseholdRetry) {

                requestHouseholdRetry = true;

                //Try to refresh token
                if (APIUtil::refreshToken()) {
                    QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this);
                    MyQNetworkRequest requestRetry(reply->request());
                    requestRetry.setupRequest(true);

                    QNetworkReply* replyRetry =  networkAccessManager->get(requestRetry);

                    bool ok = QObject::connect(replyRetry, SIGNAL(finished()), this, SLOT(onHouseholdReply()));

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

    emit sigHouseholdResponse(response, success);


}



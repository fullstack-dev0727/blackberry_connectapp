/*
 * Copyright UBT Global.
 *
 *  Created on: 03 Mar 2016
 *      Author: Lucas Bento
 */


#include "APILocalitiesRequest.hpp"


APILocalitiesRequest::APILocalitiesRequest(QObject *parent)
: QObject(parent)
{}

/*
 * APILocalitiesRequest::requestLocalities
 * Request ConnectAPI the Localities List
 */


void APILocalitiesRequest::requestLocalities(int page, QString countryId, QString newerThan)
{

    //first from database
    QString json = "";

    if (newerThan.isEmpty())
        json = mCRUDResourceTable.getResources(ResourceType::Locality, "", "", countryId, page);

    if (!json.isEmpty()) {
        emit sigLocalitiesResponse(json, true);
    }else {

        QUrl params;
        if (!countryId.isNull()  && !countryId.isEmpty())
            params.addQueryItem("countryCode", countryId);

        params.addQueryItem("page", QString::number(page));
        params.addQueryItem("sortBy", "Name");

        if (!newerThan.isNull()  && !newerThan.isEmpty()) {
            params.addQueryItem("newerThan",  newerThan);
            params.addQueryItem("itemsPerPage", QString::number(APIUtil::pageSyncSize));
        }else {
            params.addQueryItem("itemsPerPage", QString::number(APIUtil::pageSize));
        }


        QString url = APIUtil::apiLocalitiesUrl;

        if (!params.isEmpty())
            url = url + "?" + params.encodedQuery();

        MyQNetworkAccessManager* networkAccessManager = new MyQNetworkAccessManager(this);
        MyQNetworkRequest request(url, true);
        request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);
        if (!newerThan.isNull() && !newerThan.isEmpty())
            request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::AlwaysNetwork);

        QNetworkReply* reply =  networkAccessManager->get(request);

        bool ok = QObject::connect(reply, SIGNAL(finished()), this, SLOT(onLocalitiesReply()));

        Q_ASSERT(ok);
        Q_UNUSED(ok);
    }
}

/*
 * APILocalityRequest::requestLocality
 * Request ConnectAPI the Locality
 */

void APILocalitiesRequest::requestLocality(QString localityId)
{
    //first from database
    QVariantMap *reg = mCRUDResourceTable.getResource(ResourceType::Locality, localityId);
    QString json = reg->value("resource_json").toString();


    //TODO - test if no_permisson value is not null. then return , result = false and message "no_permisson".

    if (!json.isEmpty()) {
        emit sigLocalityResponse(json, true);
    }else if (!reg->value("no_permission").toString().isEmpty()) {
        emit sigLocalityResponse("no_permission", false);
    }else {

        QString url = APIUtil::apiLocalitiesUrl;
        if (!localityId.isNull())
            url = url + "/" + localityId;

        MyQNetworkAccessManager* networkAccessManager = new MyQNetworkAccessManager(this);
        MyQNetworkRequest request(url, true);
        request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);

        QNetworkReply* reply =  networkAccessManager->get(request);

        bool ok = QObject::connect(reply, SIGNAL(finished()), this, SLOT(onLocalityReply()));

        Q_ASSERT(ok);
        Q_UNUSED(ok);
    }
}


void APILocalitiesRequest::onLocalitiesReply()
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

            if (!requestLocalitiesRetry) {

                requestLocalitiesRetry = true;

                //Try to refresh token
                if (APIUtil::refreshToken()) {
                    QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this);
                    MyQNetworkRequest requestRetry(reply->request());
                    requestRetry.setupRequest(true);

                    QNetworkReply* replyRetry =  networkAccessManager->get(requestRetry);

                    bool ok = QObject::connect(replyRetry, SIGNAL(finished()), this, SLOT(onLocalitiesReply()));

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

    emit sigLocalitiesResponse(response, success);


}


void APILocalitiesRequest::onLocalityReply()
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

            if (!requestLocalityRetry) {

                requestLocalityRetry = true;

                //Try to refresh token
                if (APIUtil::refreshToken()) {
                    QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this);
                    MyQNetworkRequest requestRetry(reply->request());
                    requestRetry.setupRequest(true);

                    QNetworkReply* replyRetry =  networkAccessManager->get(requestRetry);

                    bool ok = QObject::connect(replyRetry, SIGNAL(finished()), this, SLOT(onLocalityReply()));

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

    emit sigLocalityResponse(response, success);


}


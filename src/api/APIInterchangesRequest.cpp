/*
 * Copyright UBT Global.
 *
 *  Created on: 07 Mar 2016
 *      Author: Lucas Bento
 */

#include "APIInterchangesRequest.hpp"

using namespace bb::data;

APIInterchangesRequest::APIInterchangesRequest(QObject *parent) :
        QObject(parent)
{
}

/*
 * APIInterchangesRequest::requestInterchangesByLocality(int page, QString localityId)
 * Request ConnectAPI the Subdivisions List
 */

void APIInterchangesRequest::requestInterchanges(int page, QString localityId, QString newerThan)
{
    //Request first from datrabase
    QString json = "";

    if (newerThan.isEmpty())
        json = mCRUDResourceTable.getResources(ResourceType::Interchange, localityId, "", "", page);

    JsonDataAccess dataAccess;
    const QVariantMap variant = dataAccess.loadFromBuffer(json).toMap();
    // The qvariant is a map of searches which is extracted as a list
    const QVariantList searchResults = variant["Results"].toList();
    if (!json.isEmpty() && searchResults.size() > 0) {
        qDebug() << "got from database....";
        emit sigInterchangesResponse(json, true);
    } else {
        qDebug() << "going to api....";
        QUrl params;
        if (!localityId.isNull() && !localityId.isEmpty())
            params.addQueryItem("localityId", localityId);
        if (!newerThan.isNull() && !newerThan.isEmpty()) {
            params.addQueryItem("newerThan", newerThan);
            params.addQueryItem("itemsPerPage", QString::number(APIUtil::pageSyncSize));
        }

        params.addQueryItem("itemsPerPage", QString::number(APIUtil::pageSize));
        params.addQueryItem("page", QString::number(page));

        QString url = APIUtil::apiInterchangesUrl;

        if (!params.isEmpty())
            url = url + "?" + params.encodedQuery();

        qDebug() << "interchange url:" + url;

        MyQNetworkAccessManager* networkAccessManager = new MyQNetworkAccessManager(this);
        MyQNetworkRequest request(url, true);
        request.setAttribute(QNetworkRequest::CacheLoadControlAttribute,
                QNetworkRequest::PreferCache);

        QNetworkReply* reply = networkAccessManager->get(request);

        bool ok = QObject::connect(reply, SIGNAL(finished()), this, SLOT(onInterchangesReply()));

        Q_ASSERT(ok);
        Q_UNUSED(ok);
    }
}

/*
 * APIInterchangesRequest::requestInterchange(int page, QString interchangeId)
 * Request ConnectAPI the Locality
 */

void APIInterchangesRequest::requestInterchange(int page, QString interchangeId)
{
    //Request first from datrabase
    QVariantMap *reg = mCRUDResourceTable.getResource(ResourceType::Interchange, interchangeId);
    QString json = reg->value("resource_json").toString();

    if (!json.isEmpty()) {
        emit sigInterchangeResponse(json, true);
    } else if (!reg->value("no_permission").toString().isEmpty()) {
        emit sigInterchangeResponse("no_permission", false);
    } else {

        QString url = APIUtil::apiInterchangesUrl;
        if (!interchangeId.isNull())
            url = url + "/" + interchangeId;

        MyQNetworkAccessManager* networkAccessManager = new MyQNetworkAccessManager(this);
        MyQNetworkRequest request(url, true);

        QNetworkReply* reply = networkAccessManager->get(request);

        bool ok = QObject::connect(reply, SIGNAL(finished()), this, SLOT(onInterchangeReply()));

        Q_ASSERT(ok);
        Q_UNUSED(ok);
    }
}

void APIInterchangesRequest::onInterchangesReply()
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
                    if (QCompressor::gzipDecompress(buffer, decompressed)) {
                        response = QString::fromUtf8(decompressed);
                        success = true;
                    } else {
                        response = tr("The request has failed. Check internet connection");
                        success = false;
                    }
                } else {
                    response = QString::fromUtf8(buffer);
                    success = true;
                }
            }
        } else if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 401) { //401 Unauthorized

            if (!requestInterchangesByLocalityRetry) {

                requestInterchangesByLocalityRetry = true;

                //Try to refresh token
                if (APIUtil::refreshToken()) {
                    QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this);
                    MyQNetworkRequest requestRetry(reply->request());
                    requestRetry.setupRequest(true);

                    QNetworkReply* replyRetry = networkAccessManager->get(requestRetry);

                    bool ok = QObject::connect(replyRetry, SIGNAL(finished()), this,
                            SLOT(onInterchangesReply()));

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
                if (QCompressor::gzipDecompress(buffer1, decompressed))
                    response = QString::fromUtf8(decompressed);
                else
                    response = tr("The request has failed. Check internet connection");
            } else
                response = QString::fromUtf8(buffer1);
        }

        reply->deleteLater();
    }

    if (response.trimmed().isEmpty()) {
        response = tr("Request failed. Check internet connection");
    }

    emit sigInterchangesResponse(response, success);

}

void APIInterchangesRequest::onInterchangeReply()
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
                    if (QCompressor::gzipDecompress(buffer, decompressed)) {
                        response = QString::fromUtf8(decompressed);
                        success = true;
                    } else {
                        response = tr("The request has failed. Check internet connection");
                        success = false;
                    }
                } else {
                    response = QString::fromUtf8(buffer);
                    success = true;
                }
            }
        } else if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 401) { //401 Unauthorized

            if (!requestInterchangeRetry) {

                requestInterchangeRetry = true;

                //Try to refresh token
                if (APIUtil::refreshToken()) {
                    QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this);
                    MyQNetworkRequest requestRetry(reply->request());
                    requestRetry.setupRequest(true);

                    QNetworkReply* replyRetry = networkAccessManager->get(requestRetry);

                    bool ok = QObject::connect(replyRetry, SIGNAL(finished()), this,
                            SLOT(onInterchangeReply()));

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
                if (QCompressor::gzipDecompress(buffer1, decompressed))
                    response = QString::fromUtf8(decompressed);
                else
                    response = tr("The request has failed. Check internet connection");
            } else
                response = QString::fromUtf8(buffer1);
        }

        reply->deleteLater();
    }

    if (response.trimmed().isEmpty()) {
        response = tr("Request failed. Check internet connection");
    }

    emit sigInterchangeResponse(response, success);

}


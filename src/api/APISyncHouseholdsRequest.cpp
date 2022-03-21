/*
 * Copyright UBT Global.
 *
 *  Created on: 10 Jun 2016
 *      Author: Lucas Bento
 */


#include "APISyncHouseholdsRequest.hpp"
#include "../custom/QCompressor.h"


APISyncHouseholdsRequest::APISyncHouseholdsRequest(QObject *parent)
: QObject(parent),
  requestHouseholdsRetry(false)
{
   networkAccessManager = new MyQNetworkAccessManager(this);
}


void APISyncHouseholdsRequest::requestHouseholds(int page, QString newerThan)
{

    QUrl params;

    if (page == 0)
        page = 1;

    params.addQueryItem("signPhotoUrls",  "false");
    params.addQueryItem("page",  QString::number(page));
    params.addQueryItem("itemsPerPage",  QString::number(APIUtil::pageSyncSize));
    if (!newerThan.isEmpty() && !(newerThan == "0"))
        params.addQueryItem("newerThan",  newerThan);

    QString url = APIUtil::apiHouseholdsExtendedUrl + "?" + params.encodedQuery();

    MyQNetworkRequest request(url, true);
    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::AlwaysNetwork);

    QNetworkReply* reply =  networkAccessManager->get(request);

    bool ok = QObject::connect(reply, SIGNAL(finished()), this, SLOT(onHouseholdsReply()));

    Q_ASSERT(ok);
    Q_UNUSED(ok);
}


void APISyncHouseholdsRequest::onHouseholdsReply()
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
            qDebug() << "Problem";

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

void APISyncHouseholdsRequest::requestHouseholdsActive(int page, QString newerThan)
{

    QUrl params;

    if (page == 0)
        page = 1;

    params.addQueryItem("page",  QString::number(page));
    params.addQueryItem("itemsPerPage",  QString::number(APIUtil::pageSyncSize));
    if (!newerThan.isEmpty() && !(newerThan == "0"))
        params.addQueryItem("newerThan",  newerThan);

    QString url = APIUtil::apiHouseholdsInactiveUrl + "?" + params.encodedQuery();

    MyQNetworkRequest request(url, true);
    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::AlwaysNetwork);

    QNetworkReply* reply =  networkAccessManager->get(request);

    bool ok = QObject::connect(reply, SIGNAL(finished()), this, SLOT(onHouseholdsActiveReply()));

    Q_ASSERT(ok);
    Q_UNUSED(ok);
}


void APISyncHouseholdsRequest::onHouseholdsActiveReply()
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

                    bool ok = QObject::connect(replyRetry, SIGNAL(finished()), this, SLOT(onHouseholdsActiveReply()));

                    Q_ASSERT(ok);
                    Q_UNUSED(ok);

                    return;

                }

            }
            //go to login page
            response = "loginRequest";
            success = false;


        } else {
            qDebug() << "Problem";

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

    emit sigHouseholdsActiveResponse(response, success);


}


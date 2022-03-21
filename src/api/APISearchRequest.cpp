/*
 * Copyright UBT Global.
 *
 *  Created on: 24 Feb 2016
 *      Author: Lucas Bento
 */


#include "APISearchRequest.hpp"


APISearchRequest::APISearchRequest(QObject *parent)
    : QObject(parent)
{}

void APISearchRequest::requestSearch(int page, QString searchTerm, QString resultType, QString countryCode, bool tryOfflineSearch)
{

    QString json;
    //TODO testing
    tryOfflineSearch = true;

    if (tryOfflineSearch) {

        //do search
        json = mCRUDResourceTable.searchResources(searchTerm, resultType, countryCode, page);

        if (!json.isEmpty())
            emit sigSearchResponse(json, resultType, searchTerm, page, true);
    }

    if (json.isEmpty()) {

        QUrl params;
        params.addQueryItem("page", QString::number(page));
        if(!resultType.isNull())
            params.addQueryItem("resultType", resultType);
        params.addQueryItem("countryCode", countryCode);
        params.addQueryItem("signPhotoUrls",  "false");


        QString url = APIUtil::apiSearchUrl + "/" + searchTerm +  "?" + params.encodedQuery();

        QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this);
        MyQNetworkRequest request(url, true);
        reply =  networkAccessManager->get(request);
        reply->setProperty("resultType", resultType);
        reply->setProperty("page", page);
        reply->setProperty("searchTerm", searchTerm);

        bool ok = QObject::connect(reply, SIGNAL(finished()), this, SLOT(onSearchReply()));

        Q_ASSERT(ok);
        Q_UNUSED(ok);
    }

}


void APISearchRequest::onSearchReply()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QString resultType = reply->property("resultType").toString();
    int page = reply->property("page").toInt();
    QString searchTerm = reply->property("searchTerm").toString();

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

            if (!requestSearchRetry) {

                requestSearchRetry = true;

                //Try to refresh token
                if (APIUtil::refreshToken()) {
                    QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this);
                    MyQNetworkRequest requestRetry(reply->request());
                    requestRetry.setupRequest(true);

                    QNetworkReply* replyRetry =  networkAccessManager->get(requestRetry);

                    bool ok = QObject::connect(replyRetry, SIGNAL(finished()), this, SLOT(onSearchReply()));

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

    emit sigSearchResponse(response, resultType,searchTerm, page, success);
}


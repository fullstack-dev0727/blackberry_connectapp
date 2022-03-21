/*
 * Copyright UBT Global.
 *
 *  Created on: 24 Feb 2016
 *      Author: Lucas Bento
 */


#include "APICountriesRequest.hpp"
#include "../ResourceType.h"

APICountriesRequest::APICountriesRequest(QObject *parent)
: QObject(parent),
  requestCountriesRetry(false),
  requestCountryRetry(false)
{}

/*
 * APICountriesRequest::reqCountries
 * Request ConnectAPI the Countries List
 */
void APICountriesRequest::reqCountries(int page, bool all, QString newerThan)
{
    //first from database
    QString json = "";

    if (newerThan.isEmpty()) {
        int t = all ? 7 : 6;
        json = mCRUDResourceTable.getResources(t, "",  "", "", 0); // TODO json = CRUDResourceTable::getResources(all ? ResourceType::CountryAll : ResourceType::Country, "",  "", "", 1);
    }


    if (!json.isEmpty()) {
        emit sigCountriesResponse(json, true);
    }else {
        QUrl params;
        if (!newerThan.isNull() && !newerThan.isEmpty())
            params.addQueryItem("newerThan",  newerThan);


        params.addQueryItem("page", QString::number(page));
        params.addQueryItem("itemsPerPage", QString::number(APIUtil::pageSyncSize)); //no paging

        QString url = APIUtil::apiCountriesUrl;
        if (params.hasQuery())
            url = url + + "?" + params.encodedQuery();

        MyQNetworkAccessManager* networkAccessManager = new MyQNetworkAccessManager(this);
        MyQNetworkRequest request(url, true);
        if (!newerThan.isNull() && !newerThan.isEmpty() && !(newerThan == "0"))
            request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::AlwaysNetwork);

        QNetworkReply* reply =  networkAccessManager->get(request);
        requestCountriesRetry = false;

        bool ok = QObject::connect(reply, SIGNAL(finished()), this, SLOT(onCountriesReply()));

        Q_ASSERT(ok);
        Q_UNUSED(ok);
    }
}

/*
 * APICountryRequest::reqCountries
 * Request ConnectAPI the Country information
 */


void APICountriesRequest::requestCountry(QString countryId)
{

    //Request first from datrabase
    QVariantMap *reg = mCRUDResourceTable.getResource(ResourceType::Country, countryId);
    QString json = reg->value("resource_json").toString();

    if (!json.isEmpty()) {
        emit sigCountryResponse(json, true);
    }else if (!reg->value("no_permission").toString().isEmpty()) {
        emit sigCountryResponse("no_permission", false);
    }else {

        QString url = APIUtil::apiCountriesUrl;
        if (!countryId.isNull())
            url = url + "/" + countryId;

        MyQNetworkAccessManager* networkAccessManager = new MyQNetworkAccessManager(this);
        MyQNetworkRequest request(url, true);
        request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);


        QNetworkReply* reply =  networkAccessManager->get(request);
        requestCountryRetry = false;

        bool ok = QObject::connect(reply, SIGNAL(finished()), this, SLOT(onCountryReply()));

        Q_ASSERT(ok);
        Q_UNUSED(ok);
    }
}


/*
 * APICountriesRequest::onCountriesReply
 * Manage the reply from the Countries Request
 */

void APICountriesRequest::onCountriesReply()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    reply->deleteLater();

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

            if (!requestCountriesRetry) {

                requestCountriesRetry = true;

                //Try to refresh token
                if (APIUtil::refreshToken()) {
                    QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this);
                    MyQNetworkRequest requestRetry(reply->request());
                    requestRetry.setupRequest(true);

                    QNetworkReply* replyRetry =  networkAccessManager->get(requestRetry);

                    bool ok = QObject::connect(replyRetry, SIGNAL(finished()), this, SLOT(onCountriesReply()));

                    Q_ASSERT(ok);
                    Q_UNUSED(ok);

                    return;

                }
            }

            //go to login page
            response = "requestLogin";
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

    }

    if (response.trimmed().isEmpty()) {
        response = tr("Request failed. Check internet connection");
    }

    emit sigCountriesResponse(response, success);


}

/*
 * APICountriesRequest::onCountryReply
 * Manage the reply from the Country Request
 */

void APICountriesRequest::onCountryReply()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    reply->deleteLater();



    QString response;
    bool success = false;

    QVariant fromCache = reply->attribute(QNetworkRequest::SourceIsFromCacheAttribute);
    if (fromCache.toBool())
        response = " ";

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

            if (!requestCountryRetry) {

                requestCountryRetry = true;

                //Try to refresh token
                if (APIUtil::refreshToken()) {
                    QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this);
                    MyQNetworkRequest requestRetry(reply->request());
                    requestRetry.setupRequest(true);

                    QNetworkReply* replyRetry =  networkAccessManager->get(requestRetry);

                    bool ok = QObject::connect(replyRetry, SIGNAL(finished()), this, SLOT(onCountryReply()));

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


    }

    if (response.trimmed().isEmpty()) {
        response = tr("Request failed. Check internet connection");
    }

    emit sigCountryResponse(response, success);

}

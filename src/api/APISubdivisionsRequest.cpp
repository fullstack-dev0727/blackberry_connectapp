/*
 * Copyright UBT Global.
 *
 *  Created on: 03 Mar 2016
 *      Author: Lucas Bento
 */


#include "APISubdivisionsRequest.hpp"


APISubdivisionsRequest::APISubdivisionsRequest(QObject *parent)
: QObject(parent)
{}

/*
 * APISubdivisionsRequest::requestSubdivisions
 * Request ConnectAPI the Subdivisions List
 */


void APISubdivisionsRequest::requestSubdivisions(int page, QString localityId, QString newerThan)
{
    //Request first from datrabase
    QString json;

    if (newerThan.isEmpty()) //SYNCING
        json = mCRUDResourceTable.getResources(ResourceType::Subdivision, localityId, "" ,"", page);

    if (!json.isEmpty()) {
        emit sigSubdivisionsResponse(json, true);
    }else {


        QUrl params;
        if (!localityId.isNull())
            params.addQueryItem("localityId", localityId);
        if (!newerThan.isNull() && !newerThan.isEmpty()) {
            params.addQueryItem("newerThan",  newerThan);
            params.addQueryItem("itemsPerPage",  QString::number(APIUtil::pageSyncSize));
        }

        params.addQueryItem("page",  QString::number(page));
        params.addQueryItem("itemsPerPage",  QString::number(APIUtil::pageSize));



        QString url = APIUtil::apiSubdivisionsUrl;

        if (!params.isEmpty())
            url = url + "?" + params.encodedQuery();

        MyQNetworkAccessManager* networkAccessManager = new MyQNetworkAccessManager(this);
        MyQNetworkRequest request(url, true);
        request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);
        if (!newerThan.isNull() && !newerThan.isEmpty())
            request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::AlwaysNetwork);

        QNetworkReply* reply =  networkAccessManager->get(request);

        bool ok = QObject::connect(reply, SIGNAL(finished()), this, SLOT(onSubdivisionsReply()));

        Q_ASSERT(ok);
        Q_UNUSED(ok);
    }
}

/*
 * APILocalityRequest::requestLocality
 * Request ConnectAPI the Locality
 */

void APISubdivisionsRequest::reqSubdivision(QString subdivisionId)
{
    //Request first from database
    QVariantMap *reg = mCRUDResourceTable.getResource(ResourceType::Subdivision, subdivisionId);
    QString json = reg->value("resource_json").toString();

    if (!json.isEmpty()) {
        emit sigSubdivisionResponse(json, true);
    }else if (!reg->value("no_permission").toString().isEmpty()) {
        emit sigSubdivisionResponse("no_permission", false);
    }else {


        QString url = APIUtil::apiSubdivisionsUrl;
        if (!subdivisionId.isNull())
            url = url + "/" + subdivisionId;

        MyQNetworkAccessManager* networkAccessManager = new MyQNetworkAccessManager(this);
        MyQNetworkRequest request(url, true);
        request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);

        QNetworkReply* reply =  networkAccessManager->get(request);

        bool ok = QObject::connect(reply, SIGNAL(finished()), this, SLOT(onSubdivisionReply()));

        Q_ASSERT(ok);
        Q_UNUSED(ok);
    }
}


void APISubdivisionsRequest::onSubdivisionsReply()
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

            if (!requestSubdivisionsByLocalityRetry) {

                requestSubdivisionsByLocalityRetry = true;

                //Try to refresh token
                if (APIUtil::refreshToken()) {
                    QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this);
                    MyQNetworkRequest requestRetry(reply->request());
                    requestRetry.setupRequest(true);

                    QNetworkReply* replyRetry =  networkAccessManager->get(requestRetry);

                    bool ok = QObject::connect(replyRetry, SIGNAL(finished()), this, SLOT(onSubdivisionsReply()));

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

    emit sigSubdivisionsResponse(response, success);


}


void APISubdivisionsRequest::onSubdivisionReply()
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

            if (!requestSubdivisionRetry) {

                requestSubdivisionRetry = true;

                //Try to refresh token
                if (APIUtil::refreshToken()) {
                    QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this);
                    MyQNetworkRequest requestRetry(reply->request());
                    requestRetry.setupRequest(true);

                    QNetworkReply* replyRetry =  networkAccessManager->get(requestRetry);

                    bool ok = QObject::connect(replyRetry, SIGNAL(finished()), this, SLOT(onSubdivisionReply()));

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

    if (response.trimmed().isEmpty()) {
        response = tr("Request failed. Check internet connection");
    }

    emit sigSubdivisionResponse(response, success);

}


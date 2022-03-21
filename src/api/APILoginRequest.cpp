/*
 * Copyright UBT Global.
 *
 *  Created on: 16 Feb 2016
 *      Author: Lucas Bento
 */


#include "APILoginRequest.hpp"
#include "../custom/QCompressor.h"

APILoginRequest::APILoginRequest(QObject *parent)
: QObject(parent)
{}

void APILoginRequest::requestToken(const QString &username, const QString &password)
{
    QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager(this);
    MyQNetworkRequest request(APIUtil::apiTokenUrl, false);

    QUrl params;

    params.addQueryItem("username", username);
    params.addQueryItem("password", password);

    //FIXED
    params.addQueryItem("client_id", APIUtil::clientId);
    params.addQueryItem("client_secret", APIUtil::clientSecret);
    params.addQueryItem("grant_type", APIUtil::grantTypePassword);


    QByteArray toNotEncode;
    toNotEncode.append("&");
    toNotEncode.append("*");
    toNotEncode.append("=");
    toNotEncode.append("-");
    toNotEncode.append("_");
    toNotEncode.append("~");
    toNotEncode.append(".");
    toNotEncode.append(";");
    toNotEncode.append("/");
    toNotEncode.append("?");
    toNotEncode.append(":");
    toNotEncode.append("@");
    toNotEncode.append(",");
    toNotEncode.append("$");

    QByteArray encoded = QUrl::toPercentEncoding(params.toString(), toNotEncode);
    qDebug() << encoded.remove(0,1);
    QNetworkReply* reply =  networkAccessManager->post(request, encoded);


    bool ok = QObject::connect(reply, SIGNAL(finished()), this, SLOT(onTokenReply()));

    Q_ASSERT(ok);
    Q_UNUSED(ok);
}


void APILoginRequest::onTokenReply()
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
        response = tr("Login failed. Check internet connection");
    }

    emit sigLoginResponse(response, success);
}


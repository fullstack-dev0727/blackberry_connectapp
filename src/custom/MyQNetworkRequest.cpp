/*
 * Copyright UBT Global.
 *
 *  Created on: 16 Feb 2016
 *      Author: Lucas Bento
 */

#include "MyQNetworkRequest.hpp"
#include "../api/APIUtil.hpp"
#include "../AppSettings.hpp"
#include <QNetworkDiskCache>
#include <QDir>
#include <cstdio>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QSslConfiguration>


MyQNetworkRequest::~MyQNetworkRequest(){}


/*
 * Setup the request with the Default Headers
 * Created by Lucas Bento
 */

void MyQNetworkRequest::setupRequest(bool secured) {

    //Cache
    this->setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferNetwork);

    //SSL
    QSslConfiguration config = this->sslConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1);

    this->setSslConfiguration(config);

    //SETUP
    //this->setHeader(QNetworkRequest::ContentLengthHeader,
    //    postData.count());
    this->setRawHeader( "Accept", "application/json, text/plain, */*" );
    this->setRawHeader( "Accept-Charset", "ISO-8859-1,utf-8;q=0.7,*;q=0.7" );
    this->setRawHeader( "Accept-Encoding", "gzip,deflate,qcompress" );
    this->setRawHeader( "Connection", "keep-alive" );
    this->setRawHeader( "Cache-Control","max-age=5");

    //Add Bearer Token Header
    if (secured) {
        //API CALLS
        //this->setRawHeader("Authorization", APIUtil::htmlEncodeString("Bearer " + AppSettings::getToken()));
        QString token = "Bearer " + AppSettings::getToken();
        this->setRawHeader("Authorization", token.toAscii());
        this->setHeader(QNetworkRequest::ContentTypeHeader,
            "application/json");
    }else {
        //TOKEN CALL
        this->setHeader(QNetworkRequest::ContentTypeHeader,
            "application/x-www-form-urlencoded");
    }

}

/*
 * Copyright UBT Global.
 *
 *  Created on: 16 Feb 2016
 *      Author: Lucas Bento
 */

#include "APIUtil.hpp"
#include <bb/data/JsonDataAccess>
#include "../custom/QCompressor.h"
using namespace bb::data;

//Constant
// USER: trinidad-test-user@test.com/P@ssw0rd
//const QString APIUtil::urlServer = QLatin1String("http://54.206.29.145/"); //test

// USER: zonaid.sharafi@ubteam.com/P@ssw0rd
const QString APIUtil::urlServer = QLatin1String("http://52.62.201.188/"); //Sydney - obfuscate data url
//- replace last character with x
//- reverse the result
//- remove last character from result, add it back at the front
//example;
//1. Elizabeth
//2. Elizabetx
//3. xtebazilE
//4. Extebazil
//example 2;
//1. Petar
//2. Petax
//3. xateP
//4. Pxate

const QString APIUtil::clientId = "ConnectApp";
const QString APIUtil::clientSecret = "f2437ce4-887a-49c2-ae52-2f0fe3fa228c";
const QString APIUtil::grantTypePassword = "password";
const QString APIUtil::grantTypeRefreshToken = "refresh_token";
const int APIUtil::pageSize = 15;
const int APIUtil::pageSyncSize = 100;

//Login - Token
const QString APIUtil::apiTokenUrl = urlServer + QLatin1String("Token");
const QString APIUtil::dbUnlock = QString("PRAGMA key='ub1g3!#546t';");

//Users
const QString APIUtil::apiUserSendMessageUrl = urlServer + QLatin1String("api/Members/{user}/sendemail");
const QString APIUtil::apiCurrentUserUrl = urlServer + QLatin1String("api/Users/Current");
const QString APIUtil::apiSetDefaultLocalityUrl = urlServer + QLatin1String("api/Users/{user}/defaultlocality");
const QString APIUtil::apiChangeRequestUrl = urlServer + QLatin1String("api/Users/{user}/changerequest");

//Country Config
const QString APIUtil::apiCountryConfigUrl = urlServer + QLatin1String("api/CountryConfig");

//UBT
const QString APIUtil::apiContactEmailUrl = urlServer + QLatin1String("api/UBT/contactemail"); //POST

//Search
const QString APIUtil::apiSearchUrl = urlServer + QLatin1String("api/Search"); //POST

//Countries
const QString APIUtil::apiCountriesUrl = urlServer + QLatin1String("api/Countries"); //GET

//Localities
const QString APIUtil::apiLocalitiesUrl = urlServer + QLatin1String("api/Localities"); //GET

//Subdivisions
const QString APIUtil::apiSubdivisionsUrl = urlServer + QLatin1String("api/Subdivisions"); //GET

//Households
const QString APIUtil::apiHouseholdsUrl = urlServer + QLatin1String("api/Households"); //GET
const QString APIUtil::apiHouseholdsExtendedUrl = urlServer + QLatin1String("api/Households/extended"); //GET
const QString APIUtil::apiHouseholdsInactiveUrl = urlServer + QLatin1String("api/Households/inactivehouseholds"); //GET

//Interchanges
const QString APIUtil::apiInterchangesUrl = urlServer + QLatin1String("api/Interchanges"); //GET


const QString APIUtil::apiPhotosRedirect = urlServer + QLatin1String("api/Photos/sign/redirect"); //GET

QByteArray APIUtil::htmlEncodeString(QString stringToEncode)
{
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

    return QUrl::toPercentEncoding(stringToEncode, toNotEncode);
}

bool APIUtil::refreshToken()
{

    QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager();
    MyQNetworkRequest request(APIUtil::apiTokenUrl, false);

    QUrl params;

    params.addQueryItem("refresh_token", AppSettings::getRefreshToken());

    //FIXED
    params.addQueryItem("client_id", clientId);
    params.addQueryItem("client_secret", clientSecret);

    params.addQueryItem("grant_type", grantTypeRefreshToken);

    QString p = APIUtil::htmlEncodeString(params.encodedQuery());
    QNetworkReply* reply =  networkAccessManager->post(request,  APIUtil::htmlEncodeString(params.encodedQuery()));

    //Wait for it to finish
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    //Check response
    QString response;
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

                    }
                    else {
                        response = "The request has failed. Check internet connection";

                    }
                }else {
                    response = QString::fromUtf8(buffer);

                }



                //update token
                JsonDataAccess dataAccess;
                QVariant m_loginModel = dataAccess.loadFromBuffer(response);

                //save
                AppSettings::setToken(m_loginModel.toMap().value("access_token").toString());
                AppSettings::setRefreshToken(m_loginModel.toMap().value("refresh_token").toString());

                return true;
            }
        } else {
            return false;
        }

        reply->deleteLater();
    }

    return false;

    //SSL
    /*
    QSslConfiguration config = request.sslConfiguration();
                config.setPeerVerifyMode(QSslSocket::VerifyNone);
                config.setProtocol(QSsl::TlsV1);
                request.setSslConfiguration(config)
     */

}
bool APIUtil::isConnectedToInternet() {
    QNetworkConfigurationManager *netMgr = new QNetworkConfigurationManager();
    bool isOnline = netMgr->isOnline();
    QList<QNetworkConfiguration> mNetList = netMgr->allConfigurations(QNetworkConfiguration::Active);
    int count = mNetList.count();
    return (count > 0 && isOnline);
}


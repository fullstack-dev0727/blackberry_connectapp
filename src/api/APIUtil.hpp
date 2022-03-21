/*
 * Copyright UBT Global.
 *
 *  Created on: 16 Feb 2016
 *      Author: Lucas Bento
 */

#ifndef APIUTIL_HPP
#define APIUTIL_HPP


#include <bb/data/JsonDataAccess>
#include <QtCore/QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QEventLoop>

#include <QSettings>
#include <QString>
#include <QtCore/QObject>

#include "../AppSettings.hpp"
#include "../database/SQLiteUtil.hpp"
#include "../custom/MyQNetworkRequest.hpp"
#include "../ResourceType.h"


class APIUtil
{
public:
    //Constants
    static const QString urlServer;
    static const QString clientId;
    static const QString clientSecret;
    static const QString grantTypePassword;
    static const QString grantTypeRefreshToken;
    static const int pageSize;
    static const int pageSyncSize;

    //Login - Token
    static const QString dbUnlock;
    static const QString apiTokenUrl;
    //Users
    static const QString apiCurrentUserUrl;
    static const QString apiUserSendMessageUrl;
    static const QString apiSetDefaultLocalityUrl;
    static const QString apiChangeRequestUrl;
    //CountryConfig
    static const QString apiCountryConfigUrl;
    //UBT
    static const QString apiContactEmailUrl;
    //Search
    static const QString apiSearchUrl;
    //Countries
    static const QString apiCountriesUrl;
    //Localities
    static const QString apiLocalitiesUrl;
    //Subdivisions
    static const QString apiSubdivisionsUrl;
    //Households
    static const QString apiHouseholdsUrl;
    static const QString apiHouseholdsExtendedUrl;
    static const QString apiHouseholdsInactiveUrl;

    //Interchanges
    static const QString apiInterchangesUrl;

    static const QString apiPhotosRedirect;

    static QByteArray htmlEncodeString(QString stringToEncode);
    static bool refreshToken();
    static bool isConnectedToInternet();
};

#endif



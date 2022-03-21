/*
 * Copyright UBT Global.
 *
 *  Created on: 24 Feb 2016
 *      Author: Lucas Bento
 */


#ifndef APICOUNTRIESREQUEST_HPP
#define APICOUNTRIESREQUEST_HPP

#include <QtCore/QObject>
#include "../custom/QCompressor.h"
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QDebug>
#include <bb/data/JsonDataAccess>
#include "APIUtil.hpp"
#include <bb/cascades/Application>

#include "../custom/MyQNetworkRequest.hpp"
#include "../custom/MyQNetworkAccessManager.hpp"



class APICountriesRequest : public QObject
{
    Q_OBJECT

public:
    APICountriesRequest(QObject *parent = 0);

    void reqCountries(int page, bool all,  QString newerThan);
    void requestCountry(QString countryId);

Q_SIGNALS:

    /*
     * This signal is emitted when the contries request is received
     * @param info - on success, this is the json reply from the request
     *               on failure, it is an error string
     * @param success - true if search request succeed, false if not
     */
    void sigCountriesResponse(const QString &info, bool success);
    void sigCountryResponse(const QString &info, bool success);

private Q_SLOTS:
    /*
     * Callback handler for QNetworkReply finished() signal
     */
    void onCountriesReply();
    void onCountryReply();

private:
    bool requestCountryRetry;
    bool requestCountriesRetry;

    CRUDResourceTable mCRUDResourceTable;
};
//! [0]

#endif

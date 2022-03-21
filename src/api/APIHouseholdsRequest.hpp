/*
 * Copyright UBT Global.
 *
 *  Created on: 04 Mar 2016
 *      Author: Lucas Bento
 */


#ifndef APIHOUSEHOLDSREQUEST_HPP
#define APIHOUSEHOLDSREQUEST_HPP

#include <QtCore/QObject>
#include "../custom/QCompressor.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <bb/data/JsonDataAccess>
#include "APIUtil.hpp"
#include "../database/SQLiteUtil.hpp"

#include "../custom/MyQNetworkRequest.hpp"
#include "../custom/MyQNetworkAccessManager.hpp"

class APIHouseholdsRequest : public QObject
{
    Q_OBJECT

public:
    APIHouseholdsRequest(QObject *parent = 0);

    void requestHouseholdsByLocality(int page, QString localityId);
    void requestHouseholdsBySubdivision(int page, QString subdivisionId);

    void requestHousehold(QString householdId);
private:
    bool requestHouseholdsRetry;
    bool requestHouseholdRetry;

    void requestHouseholds(int page, QUrl params);

Q_SIGNALS:

    /*
     * This signal is emitted when the households request is received
     * @param info - on success, this is the json reply from the request
     *               on failure, it is an error string
     * @param success - true if search request succeed, false if not
     */
    void sigHouseholdsResponse(const QString &info, bool success);
    void sigHouseholdResponse(const QString &info, bool success);

private Q_SLOTS:
    /*
     * Callback handler for QNetworkReply finished() signal
     */
    void onHouseholdsReply();
    void onHouseholdReply();

private:
    CRUDResourceTable mCRUDResourceTable;
};
//! [0]

#endif

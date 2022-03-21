/*
 * Copyright UBT Global.
 *
 *  Created on: 10 Jun 2016
 *      Author: Lucas Bento
 */


#ifndef APISYNCHOUSEHOLDSREQUEST_HPP
#define APISYNCHOUSEHOLDSREQUEST_HPP

#include <QtCore/QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <bb/data/JsonDataAccess>
#include "APIUtil.hpp"

#include "../custom/MyQNetworkRequest.hpp"
#include "../custom/MyQNetworkAccessManager.hpp"

class APISyncHouseholdsRequest : public QObject
{
    Q_OBJECT

public:
    APISyncHouseholdsRequest(QObject *parent = 0);

    void requestHouseholds(int page, QString newerThan);
    void requestHouseholdsActive(int page, QString newerThan);

private:
    bool requestHouseholdsRetry;
    bool requestHouseholdsActiveRetry;
    MyQNetworkAccessManager* networkAccessManager;

Q_SIGNALS:

    /*
     * This signal is emitted when the households request is received
     * @param info - on success, this is the json reply from the request
     *               on failure, it is an error string
     * @param success - true if search request succeed, false if not
     */
    void sigHouseholdsResponse(const QString &info, bool success);
    void sigHouseholdsActiveResponse(const QString &info, bool success);

private Q_SLOTS:
    /*
     * Callback handler for QNetworkReply finished() signal
     */
    void onHouseholdsReply();
    void onHouseholdsActiveReply();
};
//! [0]

#endif

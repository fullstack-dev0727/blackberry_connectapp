/*
 * Copyright UBT Global.
 *
 *  Created on: 02 Mar 2016
 *      Author: Lucas Bento
 */


#ifndef APILOCALITIESREQUEST_HPP
#define APILOCALITIESREQUEST_HPP

#include <QtCore/QObject>
#include "../custom/QCompressor.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkDiskCache>
#include <QUrl>
#include <QDebug>
#include <bb/data/JsonDataAccess>

#include "../custom/MyQNetworkRequest.hpp"
#include "../custom/MyQNetworkAccessManager.hpp"
#include "APIUtil.hpp"


class APILocalitiesRequest : public QObject
{
    Q_OBJECT

public:
    APILocalitiesRequest(QObject *parent = 0);

    void requestLocalities(int page,QString countryId, QString newerThan);
    void requestLocality(QString localityId);

Q_SIGNALS:

    /*
     * This signal is emitted when the localities request is received
     * @param info - on success, this is the json reply from the request
     *               on failure, it is an error string
     * @param success - true if search request succeed, false if not
     */
    void sigLocalitiesResponse(const QString &info, bool success);
    void sigLocalityResponse(const QString &info, bool success);

private Q_SLOTS:
    /*
     * Callback handler for QNetworkReply finished() signal
     */
    void onLocalitiesReply();
    void onLocalityReply();
private:
    bool requestLocalitiesRetry;
    bool requestLocalityRetry;

    CRUDResourceTable mCRUDResourceTable;
};
//! [0]

#endif

/*
 * Copyright UBT Global.
 *
 *  Created on: 07 Mar 2016
 *      Author: Lucas Bento
 */


#ifndef APIINTERCHANGESREQUEST_HPP
#define APIINTERCHANGESREQUEST_HPP

#include <QtCore/QObject>
#include "../custom/QCompressor.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <bb/data/JsonDataAccess>

#include "../custom/MyQNetworkRequest.hpp"
#include "../custom/MyQNetworkAccessManager.hpp"
#include "APIUtil.hpp"


class APIInterchangesRequest : public QObject
{
    Q_OBJECT

public:
    APIInterchangesRequest(QObject *parent = 0);

    void requestInterchanges(int page, QString localityId, QString newerThan);
    void requestInterchange(int page,QString interchangeId);

Q_SIGNALS:

    /*
     * This signal is emitted when the Interchanges request is received
     * @param info - on success, this is the json reply from the request
     *               on failure, it is an error string
     * @param success - true if search request succeed, false if not
     */
    void sigInterchangesResponse(const QString &info, bool success);
    void sigInterchangeResponse(const QString &info, bool success);

private Q_SLOTS:
    /*
     * Callback handler for QNetworkReply finished() signal
     */
    void onInterchangesReply();
    void onInterchangeReply();
private:
    bool requestInterchangesByLocalityRetry;
    bool requestInterchangeRetry;

    CRUDResourceTable mCRUDResourceTable;
};
//! [0]

#endif

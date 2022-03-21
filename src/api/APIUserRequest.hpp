/*
 * Copyright UBT Global.
 *
 *  Created on: 16 Feb 2016
 *      Author: Lucas Bento
 */


#ifndef APIUSERREQUEST_HPP
#define APIUSERREQUEST_HPP

#include <QtCore/QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QDebug>
#include "../custom/QCompressor.h"
#include "../custom/MyQNetworkRequest.hpp"
#include "APIUtil.hpp"
#include "../custom/MyQNetworkAccessManager.hpp"


class APIUserRequest : public QObject
{
    Q_OBJECT

public:
    APIUserRequest(QObject *parent = 0);

    void requestCurrentUser();
    void setDefaultLocality(QString defaulLocalityId, QString userId);
    void changeReq(QVariantMap changingRequest);

Q_SIGNALS:

    /*
     * This signal is emitted when the logged user request is received
     * @param info - on success, this is the json reply from the request
     *               on failure, it is an error string
     * @param success - true if search request succeed, false if not
     */
    void sigCurrentUserResponse(const QString &info, bool success);


    void sigSetDefaultLocalityResponse(const QString &info, bool success);

    void sigSendChangeResquestResponse(const QString &info, bool success);
private Q_SLOTS:
    /*
     * Callback handler for QNetworkReply finished() signal
     */
    void onCurrentUserReply();

    void onSetDefaultLocalityReply();

    void onSendChangeRequestReply();

private:

    bool requestSendRequestRetry;
    bool requestCurrentUserRetry;
    bool requestSetDefaultLocalityRetry;

    CRUDResourceTable mCRUDResourceTable;
};
//! [0]

#endif

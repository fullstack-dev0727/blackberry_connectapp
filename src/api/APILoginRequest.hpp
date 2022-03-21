/*
 * Copyright UBT Global.
 *
 *  Created on: 16 Feb 2016
 *      Author: Lucas Bento
 */


#ifndef APILOGINREQUEST_HPP
#define APILOGINREQUEST_HPP

#include <QtCore/QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QDebug>
#include "../custom/QCompressor.h"
#include "../custom/MyQNetworkRequest.hpp"
#include "../custom/MyQNetworkAccessManager.hpp"
#include "APIUtil.hpp"


class APILoginRequest : public QObject
{
    Q_OBJECT

public:
    APILoginRequest(QObject *parent = 0);
    void requestToken(const QString &username, const QString &password);
Q_SIGNALS:

    /*
     * This signal is emitted when the login request is received
     * @param info - on success, this is the json reply from the request
     *               on failure, it is an error string
     * @param success - true if search request succeed, false if not
     */
    void sigLoginResponse(const QString &info, bool success);

private Q_SLOTS:
    /*
     * Callback handler for QNetworkReply finished() signal
     */
    void onTokenReply();
};
//! [0]

#endif

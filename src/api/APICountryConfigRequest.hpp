/*
 * Copyright UBT Global.
 *
 *  Created on: 16 Feb 2016
 *      Author: Lucas Bento
 */


#ifndef APICOUNTRYCONFIGREQUEST_HPP
#define APICOUNTRYCONFIGREQUEST_HPP

#include <QtCore/QObject>
#include "../custom/QCompressor.h"
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QDebug>
#include "APIUtil.hpp"
#include <bb/data/JsonDataAccess>

#include "../AppSettings.hpp"
#include "../custom/MyQNetworkAccessManager.hpp"
#include "../custom/MyQNetworkRequest.hpp"

class APICountryConfigRequest : public QObject
{
    Q_OBJECT

public:
    APICountryConfigRequest(QObject *parent = 0);

    void requestCountryConfig();
    void sendCtcEmail(const QString &userId, const QString &subject, const QString &body);


Q_SIGNALS:

    /*
     * This signal is emitted when the terms and coditions request is received
     * @param info - on success, this is the json reply from the request
     *               on failure, it is an error string
     * @param success - true if search request succeed, false if not
     */
    void sigCountryConfigResponse(const QString &info, bool success);
    void sigContactEmailResponse(const QString &info, bool success);

private Q_SLOTS:
    /*
     * Callback handler for QNetworkReply finished() signal
     */
    void onCountryConfigReply();
    void onContactEmailReply();
private:
    bool requestCountryConfigRetry;
    bool sendContactEmailRetry;
    CRUDResourceTable mCRUDResourceTable;

};
//! [0]

#endif

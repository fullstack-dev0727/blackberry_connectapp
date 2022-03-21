/*
 * Copyright UBT Global.
 *
 *  Created on: 24 Feb 2016
 *      Author: Lucas Bento
 */


#ifndef APISEARCHREQUEST_HPP
#define APISEARCHREQUEST_HPP

#include <QtCore/QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QDebug>
#include "../custom/QCompressor.h"
#include "../custom/MyQNetworkRequest.hpp"
#include "../custom/MyQNetworkAccessManager.hpp"
#include "APIUtil.hpp"

class APISearchRequest : public QObject
{
    Q_OBJECT

public:
    APISearchRequest(QObject *parent = 0);

    void requestSearch(int page, QString searchTerm, QString resultType, QString countryCode, bool tryOfflineSearch);

    QNetworkReply* reply;

Q_SIGNALS:

    /*
     * This signal is emitted when the search request is received
     * @param info - on success, this is the json reply from the request
     *               on failure, it is an error string
     * @param success - true if search request succeed, false if not
     */
    void sigSearchResponse(const QString &info, const QString &resultType, const QString &searchTerm, int page, bool success);

private Q_SLOTS:
    /*
     * Callback handler for QNetworkReply finished() signal
     */
    void onSearchReply();
private:
    bool requestSearchRetry;

    CRUDResourceTable mCRUDResourceTable;
};
//! [0]

#endif

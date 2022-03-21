/*
 * Copyright UBT Global.
 *
 *  Created on: 02 Mar 2016
 *      Author: Lucas Bento
 */


#ifndef APISUBDIVISIONSREQUEST_HPP
#define APISUBDIVISIONSREQUEST_HPP

#include <QtCore/QObject>
#include "../custom/QCompressor.h"
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QDebug>
#include <bb/data/JsonDataAccess>

#include "../custom/MyQNetworkRequest.hpp"
#include "../custom/MyQNetworkAccessManager.hpp"
#include "APIUtil.hpp"

class APISubdivisionsRequest : public QObject
{
    Q_OBJECT

public:
    APISubdivisionsRequest(QObject *parent = 0);

    void requestSubdivisions(int page, QString localityId, QString newerThan);
    void reqSubdivision(QString subdivisionId);

Q_SIGNALS:

    /*
     * This signal is emitted when the subdivisions request is received
     * @param info - on success, this is the json reply from the request
     *               on failure, it is an error string
     * @param success - true if search request succeed, false if not
     */
    void sigSubdivisionsResponse(const QString &info, bool success);
    void sigSubdivisionResponse(const QString &info, bool success);

private Q_SLOTS:
    /*
     * Callback handler for QNetworkReply finished() signal
     */
    void onSubdivisionsReply();
    void onSubdivisionReply();
private:
    bool requestSubdivisionsByLocalityRetry;
    bool requestSubdivisionRetry;

    CRUDResourceTable mCRUDResourceTable;
};
//! [0]

#endif

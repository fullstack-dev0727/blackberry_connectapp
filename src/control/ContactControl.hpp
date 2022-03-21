/*
 * Copyright UBT Global.
 *
 *  Created on: 22 Feb 2016
 *      Author: Lucas Bento
 */

#ifndef CONTACTCONTROL_HPP
#define CONTACTCONTROL_HPP


#include "../AppUi.hpp"
#include <bb/cascades/QListDataModel>
#include <bb/cascades/GroupDataModel>
#include <QtCore/QObject>
#include <bb/cascades/NavigationPane>

#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/ActivityIndicator>

#include <bb/data/JsonDataAccess>
#include <bb/utility/i18n/RelativeDateFormatter>

#include <unistd.h>
#include "../custom/BaseControl.h"
using namespace bb::cascades;

/**
 * This class deals mainly with Contacting UBT
 */

class ContactControl : public BaseControl
{
    Q_OBJECT

    Q_PROPERTY(bool active READ active NOTIFY activeChanged)
    Q_PROPERTY(bool error READ error NOTIFY statusChanged)
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY statusChanged)
    Q_PROPERTY(QString userName READ userName NOTIFY userInfoChanged)
    Q_PROPERTY(QString userId READ userId NOTIFY userInfoChanged)

    Q_PROPERTY(QVariantMap m_ContactInfo READ contactInfo NOTIFY ctScreenStatusChanged )

public:
    ContactControl(QObject *parent = 0);
    void setHomeSource(AbstractPane *root = 0);

    void setRoot(Page *root = 0);
    void setUserInfo(QString userId, QString userName);

public Q_SLOTS:
    void requestContactInfo();

    void sendContactEmail(const QString &subject, const QString &body);
    void sendUserEmail(const QString userId, const QString &subject, const QString &body);

    void tCallNumber(QString number);

    void reset();
    Q_INVOKABLE QString dateFromTimestamp(const QString &timestamp);

Q_SIGNALS:
    void activeChanged();
    void statusChanged();
    void userInfoChanged();
    void ctScreenStatusChanged();
    void ctMessageSent();
    void ctFinished();

private Q_SLOTS:
    /*
     * Handles the complete signal from Country Config request
     * the request is complete
     * @see LoginRequest::complete()
     */
    void onContactInfoResponse(const QString &info, bool success);

    /*
     * Handles the complete signal from Email Sending request
     * the request is complete
     * @see LoginRequest::complete()
     */
    void onSentEmailResponse(const QString &info, bool success);

private:
    /*
     * Parses the JSON response
     */
    void parseContactInfoResponse(const QString&);
    void parseSentEmailResponse(const QString&);


    bool active() const;
    bool error() const;
    QString userName() const;
    QString userId() const;
    QString errorMessage() const;

    QVariantMap contactInfo() const;

private:
    AbstractPane *homeSource;
    Page *rootSource;
    ActivityIndicator* m_ActivityIndicator;
    bool m_active;
    bool m_error;
    QString m_errorMessage;
    QString m_userId;
    QString m_userName;

    QVariantMap m_ContactInfo;
};

#endif

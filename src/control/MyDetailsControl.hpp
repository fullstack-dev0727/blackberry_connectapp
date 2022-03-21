/*
 * Copyright UBT Global.
 *
 *  Created on: 22 Feb 2016
 *      Author: Lucas Bento
 */

#ifndef MYDETAILSCONTROL_HPP
#define MYDETAILSCONTROL_HPP


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
#include "../api/APIHouseholdsRequest.hpp"
#include "../api/APIUserRequest.hpp"
#include "../imgutil/imageitem.hpp"
#include <unistd.h>
#include "../custom/BaseControl.h"
using namespace bb::cascades;

/**
 * This class deals mainly with My Details
 */

class MyDetailsControl : public BaseControl
{
    Q_OBJECT

    Q_PROPERTY(bool familyUpdates READ familyUpdates NOTIFY familyUpdatesChanged)
    Q_PROPERTY(bool photoUpdates READ photoUpdates NOTIFY photoUpdatesChanged)
    Q_PROPERTY(bool displayWorkPhone READ displayWorkPhone NOTIFY displayWorkPhoneChanged)
    Q_PROPERTY(bool displayMobilePhone READ displayMobilePhone NOTIFY displayMobilePhoneChanged)
    Q_PROPERTY(QString comments READ comments NOTIFY commentsChanged)
    Q_PROPERTY(QString emailAddress READ emailAddress NOTIFY emailAddressChanged)
    Q_PROPERTY(QString address READ address NOTIFY addressChanged)
    Q_PROPERTY(QString workPhone READ workPhone NOTIFY workPhoneChanged)
    Q_PROPERTY(QString homePhone READ homePhone NOTIFY homePhoneChanged)
    Q_PROPERTY(QString mobilePhone READ mobilePhone NOTIFY mobilePhoneChanged)

    Q_PROPERTY(bool active READ active NOTIFY activeChanged)
    Q_PROPERTY(bool error READ error NOTIFY statusChanged)
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY statusChanged)

    Q_PROPERTY(QObject* myDetails READ myDetails NOTIFY myDetailsChanged )

public:
    MyDetailsControl(QObject *parent = 0);
    void setHomeSource(AbstractPane *root = 0);

    void setRoot(Page *root = 0);



public Q_SLOTS:
    //void requestMyDetails();
    void sendChangeRequest();
    void manageSubs();
    void requestHousehold();
    void setComments(QString comment);
    void setEmailAddress(QString email_address);
    void setAddress(QString address);
    void setPhotoUpdates(bool photoUpdates);
    void setFamilyUpdates(bool familyUpdates);
    void setDisplayWorkPhone(bool displayWorkPhone);
    void setDisplayMobilePhone(bool displayMobilePhone);
    void setWorkPhone(QString work_phone);
    void setMobilePhone(QString mobile_phone);
    void setHomePhone(QString home_phone);

    void reset();
    Q_INVOKABLE QString dateFromTimestamp(const QString &timestamp);

Q_SIGNALS:
    void activeChanged();
    void statusChanged();
    void commentsChanged();
    void familyUpdatesChanged();
    void photoUpdatesChanged();
    void displayWorkPhoneChanged();
    void displayMobilePhoneChanged();
    void myDetailsChanged();
    void changeRequestSent();
    void emailAddressChanged();
    void addressChanged();
    void homePhoneChanged();
    void workPhoneChanged();
    void mobilePhoneChanged();

private Q_SLOTS:
    //void onMyDetailsResponse(const QString &info, bool success);
    void onHouseholdResponse(const QString &info, bool success);

    /*
     * Handles the complete signal from Email Sending request
     * the request is complete
     * @see LoginRequest::complete()
     */
    void onSendChangeRequestResponse(const QString &info, bool success);

private:
    /*
     * Parses the JSON response
     */
    //void parseMyDetailsResponse(const QString&);
    void parseSendChangeRequestResponse(const QString&);
    void parseHouseholdResponse(const QString&);

    bool familyUpdates() const;
    bool photoUpdates() const;
    bool displayWorkPhone() const;
    bool displayMobilePhone() const;
    QString comments() const;
    QString emailAddress() const;
    QString address() const;
    QString homePhone() const;
    QString workPhone() const;
    QString mobilePhone() const;

    bool active() const;
    bool error() const;
    QString errorMessage() const;

    ImageItem* myDetails() const;

private:
    AbstractPane *homeSource;
    Page *rootSource;
    ActivityIndicator* m_ActivityIndicator;
    bool m_active;
    bool m_error;
    QString m_errorMessage;
    ImageItem* m_mydetails;

    QString m_emailAddress;
    QString m_address;
    QString m_homePhone;
    QString m_workPhone;
    QString m_mobilePhone;
    bool m_familyUpdates;
    bool m_photoUpdates;
    bool m_displayWorkPhone;
    bool m_displayMobilePhone;
    QString m_comments;

};

#endif

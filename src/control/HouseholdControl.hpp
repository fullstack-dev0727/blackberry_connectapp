/*
 * Copyright UBT Global.
 *
 *  Created on: 08 Mar 2016
 *      Author: Lucas Bento
 */

#ifndef HOUSEHOLDCONTROL_HPP
#define HOUSEHOLDCONTROL_HPP


#include "../AppUi.hpp"
#include <bb/cascades/QListDataModel>
#include <bb/cascades/GroupDataModel>
#include <QtCore/QObject>
#include <bb/cascades/NavigationPane>
#include <bb/cascades/ListView>

#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/ActivityIndicator>

#include <bb/data/JsonDataAccess>
#include <bb/utility/i18n/RelativeDateFormatter>

#include "../api/APIHouseholdsRequest.hpp"
#include "../AppSettings.hpp"
#include "HomeControl.hpp"
#include "../custom/BaseControl.h"
#include <unistd.h>

using namespace bb::cascades;

/**
 * This class deals mainly with Household Requests and Control
 */

class HouseholdControl : public BaseControl
{
    Q_OBJECT

    Q_PROPERTY(bool hdImage READ hdImage NOTIFY hdImageChanged)
    Q_PROPERTY(bool active READ active NOTIFY activeChanged)
    Q_PROPERTY(bool noPermission READ noPermission NOTIFY noPermissionChanged)
    Q_PROPERTY(bool error READ error NOTIFY statusChanged)
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY statusChanged)

    Q_PROPERTY(QVariantMap m_householdModel READ householdModel NOTIFY householdChanged )
    Q_PROPERTY(bb::cascades::DataModel* m_contentModel READ contentModel NOTIFY contentChanged )


public:
    HouseholdControl(QObject *parent = 0);
    void setHomeSource(AbstractPane *root = 0);

    void setRoot(Page *root = 0);



public Q_SLOTS:
    void openAction(QString id);
    void requestHousehold(QString householdId);

    //Listview content
    void requestMembers();

    void tCallNumber(QString number, QString name);
    void tSendEmail();
    void openHouseholder(QString householderId);
    void openLocality(QString localityId);
    void openSubdivision(QString subdivisionId);

    void manageSubs();
    QByteArray encodeQString(const QString& toEncode);

    void openUpgradeAccount();

    void onDialogCallFinished(
            bb::system::SystemUiResult::Type type);


    void reset();
    Q_INVOKABLE QString dateFromTimestamp(const QString &timestamp);

Q_SIGNALS:
    void activeChanged();
    void statusChanged();
    void hdImageChanged();
    void householdChanged();
    void noPermissionChanged();

    void contentChanged();
private Q_SLOTS:
    /*
     * Handles the complete signal from household request when
     * the request is complete
     */
    void onHouseholdResponse(const QString &info, bool success);
    QVariantMap householdModel() const;
private:
    /*
     * Parses the JSON response
     */
    void parseHouseholdResponse(const QString&);

    bool active() const;
    bool error() const;
    bool hdImage() const;
    bool noPermission() const;
    QString errorMessage() const;


    bb::cascades::DataModel* contentModel() const;



private:
    AbstractPane *homeSource;

    Page *rootSource;
    ActivityIndicator* m_ActivityIndicator;
    ActivityIndicator* m_ContentIndicator;
    bool m_active;
    bool m_error;
    bool m_hdImage;
    QString m_errorMessage;
    QVariantMap m_householdModel;



    bb::system::SystemDialog* m_callDialog;


    QString m_householdId;
    bb::cascades::QListDataModel<QObject*>* m_contentModel;
    ListView* m_ListView;

    bool m_noPermission;

    QString numberToCall;

};

#endif

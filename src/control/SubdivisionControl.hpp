/*
 * Copyright UBT Global.
 *
 *  Created on: 08 Mar 2016
 *      Author: Lucas Bento
 */

#ifndef SUBDIVISIONCONTROL_HPP
#define SUBDIVISIONCONTROL_HPP


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

#include "../api/APISubdivisionsRequest.hpp"
#include "../api/APIHouseholdsRequest.hpp"
#include "../AppSettings.hpp"
#include "HomeControl.hpp"
#include "../custom/BaseControl.h"

#include <unistd.h>

using namespace bb::cascades;


class SubdivisionWorker : public QObject
{
    Q_OBJECT
    QThread workerThread;

public Q_SLOTS:
    void requestSubdivision(QString subdivisionId);
    //Listview content
    void requestHouseholds(int page, QString subdivisionId);

    void onSubdivisionResponse(const QString &info, bool success);
    //Listview content
    void onRequestHouseholdsResponse(const QString &info, bool success);

    Q_SIGNALS:
        void resultSubdivisionReady(const QVariant &);

        void resultHouseholdsReady(const QVariantList &);

        void requestlogin();
        void errorOcurred(const QString &);
        void noPermission();


    public:
        int m_subdivisionId;
};


/**
 * This class deals mainly with Subdivision Requests and Control
 */
class SubdivisionControl : public BaseControl
{
    Q_OBJECT
    QThread workerThread;

    Q_PROPERTY(bool error READ error NOTIFY statusChanged)
    Q_PROPERTY(bool noPermission READ noPermission NOTIFY noPermissionChanged)
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY statusChanged)

    Q_PROPERTY(QVariantMap m_subdivisionModel READ subdivisionModel NOTIFY subdivisionChanged )
    Q_PROPERTY(bb::cascades::DataModel* m_contentModel READ contentModel NOTIFY contentChanged )


public:
    SubdivisionControl(QObject *parent = 0);
    void setHomeSource(AbstractPane *root = 0);

    void setRoot(Page *root = 0);

    QString id;

    void load();

public Q_SLOTS:
    void openAction(QString id);
    void requestSubdivision(QString subdivisionId);
    //Listview content
    void requestHouseholds(int page);

    void openHousehold(QString householdId, QString name);
    void openLocality(QString localityId);
    QByteArray encodeQString(const QString& toEncode);

    void manageSubs();


    QString getId();

    void reset();
    Q_INVOKABLE QString dateFromTimestamp(const QString &timestamp);

Q_SIGNALS:
    void statusChanged();
    void subdivisionChanged();
    void contentChanged();
    void loadSubdivision();
    void noPermissionChanged();

    void doRequestSubdivision(const QString &);
    void doRequestHouseholds(const int &, const QString &);


private Q_SLOTS:

    void onAtEndChanged(bool atEnd);


    void handleSubdivisionResult(const QVariant &result);
    void handleHouseholdsResult(const QVariantList &results);

    void handleError(const QString &error);
    void handleLoginRequest();

    void handleNoPermission();


private:
    bool error() const;
    QString errorMessage() const;
    bool noPermission() const;

    QVariantMap subdivisionModel() const;
    bb::cascades::DataModel* contentModel() const;


private:
    AbstractPane *homeSource;

    Page *rootSource;
    ActivityIndicator* m_ActivityIndicator;
    ActivityIndicator* m_ContentIndicator;
    bool m_active;
    bool m_error;
    QString m_errorMessage;
    QVariantMap m_subdivisionModel;


    QString m_subdivisionId;
    bb::cascades::QListDataModel<QObject*>* m_contentModel;
    ListView* m_ListView;

    bool loadingMore;

    bool m_noPermission;


};

#endif

/*
 * Copyright UBT Global.
 *
 *  Created on: 03 Mar 2016
 *      Author: Lucas Bento
 */

#ifndef LOCALITYCONTROL_HPP
#define LOCALITYCONTROL_HPP


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

#include "../api/APILocalitiesRequest.hpp"
#include "../api/APIHouseholdsRequest.hpp"
#include "../api/APISubdivisionsRequest.hpp"
#include "../api/APIInterchangesRequest.hpp"
#include "../AppSettings.hpp"
#include "HomeControl.hpp"
#include "../custom/BaseControl.h"

#include <unistd.h>

using namespace bb::cascades;


class LocalityWorker : public QObject
{
    Q_OBJECT
    QThread workerThread;

public Q_SLOTS:
    void requestLocality(QString localityId);
    //Listview content
    void requestHouseholds(int page, QString m_localityId);
    void requestSubdivisions(int page, QString m_localityId);
    void requestInterchanges(int page, QString m_localityId);

    void onLocalityResponse(const QString &info, bool success);
    //Listview content
    void onRequestHouseholdsResponse(const QString &info, bool success);
    void onRequestSubdivisionsResponse(const QString &info, bool success);
    void onRequestInterchangesResponse(const QString &info, bool success);

    Q_SIGNALS:
        void resultLocalityReady(const QVariant &);

        void resultHouseholdsReady(const QVariantList &);
        void resultSubdivisionsReady(const QVariantList &);
        void resultInterchangesReady(const QVariantList &);

        void requestlogin();
        void errorOcurred(const QString &);
        void noPermission();

    public:
        int m_localityId;
};


class LocalityControl : public BaseControl
{
    Q_OBJECT
    QThread workerThread;

    Q_PROPERTY(bool error READ error NOTIFY statusChanged)
    Q_PROPERTY(bool noPermission READ noPermission NOTIFY noPermissionChanged)
    Q_PROPERTY(int defaultLocality READ defaultLocality NOTIFY defaultLocalityChanged)
    Q_PROPERTY(int oldDefaultLocality READ oldDefaultLocality NOTIFY oldDefaultLocalityChanged)

    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY statusChanged)

    Q_PROPERTY(QVariantMap m_localityModel READ localityModel NOTIFY localityChanged )
    Q_PROPERTY(bb::cascades::DataModel* m_contentModel READ contentModel NOTIFY contentChanged )


public:
    LocalityControl(QObject *parent = 0);
    ~LocalityControl();
    void setHomeSource(AbstractPane *root = 0);

    void setRoot(Page *root = 0);




public Q_SLOTS:
    void openAction(QString id);
    void requestSetDefaultLocality(QString localityId);


    void openSubdivision(QString subdivisionId, QString name);
    void openHousehold(QString householdId, QString name);
    void openLocality(QString localityId, QString localityName);

    void setAsDefaultLocality();
    void setOldAsDefaultLocality();

    void reset();
    Q_INVOKABLE QString dateFromTimestamp(const QString &timestamp);

    void manageSubs();


    void requestLocality(QString localityId);
    //Listview content
    void requestHouseholds(int page);
    void requestSubdivisions(int page);
    void requestInterchanges(int page);

Q_SIGNALS:
    void statusChanged();
    void localityChanged();
    void defaultLocalityChanged();
    void oldDefaultLocalityChanged();
    void setDefaultLocalityChanged();
    void noPermissionChanged();

    void doRequestLocality(const QString &);
    void doRequestHouseholds(const int &, const QString &);
    void doRequestSubdivisions(const int &, const QString &);
    void doRequestInterchanges(const int &, const QString &);

    void contentChanged();
private Q_SLOTS:
    /*
     * Handles the complete signal from locality request when
     * the request is complete
     */
    void onSetDefaultLocalityResponse(const QString &info, bool success);
    void onAtEndChanged(bool atEnd);

    void handleLocalityResult(const QVariant &result);

    void handleHouseholdsResult(const QVariantList &results);
    void handleSubdivisionsResult(const QVariantList &results);
    void handleInterchangesResult(const QVariantList &results);

    void handleError(const QString &error);

    void handleNoPermission();

    void handleLoginRequest();


private:
    bool error() const;
    bool noPermission() const;
    int defaultLocality() const;
    int oldDefaultLocality() const;

    QString errorMessage() const;

    QVariantMap localityModel() const;
    bb::cascades::DataModel* contentModel() const;

private:
    AbstractPane *homeSource;

    Page *rootSource;
    ActivityIndicator* m_ActivityIndicator;
    ActivityIndicator* m_ActivityMoreIndicator;
    ActivityIndicator* m_ActivityContentIndicator;
    bool m_active;
    bool m_error;
    QString m_errorMessage;
    QVariantMap m_localityModel;

    QString m_localityId;
    bb::cascades::QListDataModel<QObject*>* m_contentModel;
    bb::cascades::QListDataModel<QObject*>* m_householdsModel;
    bb::cascades::QListDataModel<QObject*>* m_subdivisionsModel;
    bb::cascades::QListDataModel<QObject*>* m_interchangesModel;
    ListView* m_ListView;

    bool loadingMore;
    int m_currentTab;
    int m_defaultlocality;
    int m_oldDefaultlocality;
    APILocalitiesRequest* request;

    bool m_noPermission;
};

#endif

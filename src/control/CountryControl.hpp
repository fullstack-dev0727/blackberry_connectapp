/*
 * Copyright UBT Global.
 *
 *  Created on: 04 Mar 2016
 *      Author: Lucas Bento
 */

#ifndef COUNTRYCONTROL_HPP
#define COUNTRYCONTROL_HPP


#include "../AppUi.hpp"
#include <bb/cascades/QListDataModel>
#include <bb/cascades/GroupDataModel>
#include <QtCore/QObject>
#include <bb/cascades/NavigationPane>

#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/ActivityIndicator>
#include <bb/cascades/ListView>

#include <bb/data/JsonDataAccess>
#include <bb/utility/i18n/RelativeDateFormatter>

#include <unistd.h>

#include "../api/APICountriesRequest.hpp"
#include "../api/APILocalitiesRequest.hpp"
#include "../custom/PagedDataModel.hpp"
#include "../AppSettings.hpp"
#include "HomeControl.hpp"
#include "BrowseOtherCountriesControl.hpp"
#include "../custom/BaseControl.h"
using namespace bb::cascades;

/**
 * This class deals mainly with Contacting UBT
 */

class CountryControl : public BaseControl
{
    Q_OBJECT

    Q_PROPERTY(bool active READ active NOTIFY activeChanged)
    Q_PROPERTY(bool noPermission READ noPermission NOTIFY noPermissionChanged)
    Q_PROPERTY(bool error READ error NOTIFY statusChanged)
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY statusChanged)
    Q_PROPERTY(QString currentLocalityName READ currentLocalityName NOTIFY currentLocalityNameChanged)

    Q_PROPERTY(QVariantMap m_countryModel READ countryModel NOTIFY countryChanged )
    Q_PROPERTY(PagedDataModel* m_localitiesModel READ localitiesModel NOTIFY localitiesChanged )

public:
    CountryControl(QObject *parent = 0);
    void setHomeSource(AbstractPane *root = 0);

    void setRoot(Page *root = 0);



public Q_SLOTS:
    void openAction(QString id);


    void requestCountry(QString countryCode);
    void requestLocalities(QString countryCode, int page);

    void openLocality(QString localityId, QString name);

    void manageSubs();

    void reset();
    void browseOtherCountries();
    Q_INVOKABLE QString dateFromTimestamp(const QString &timestamp);

Q_SIGNALS:
    void activeChanged();
    void statusChanged();
    void countryChanged();
    void localitiesChanged();
    void currentLocalityNameChanged();
    void noPermissionChanged();

private Q_SLOTS:
    /*
     * Handles the complete signal from locality request when
     * the request is complete
     */
    void onCountryResponse(const QString &info, bool success);
    void onRequestLocalitiesResponse(const QString &info, bool success);
    void onAtEndChanged(bool atEnd);
private:
    /*
     * Parses the JSON response
     */
    void parseCountryResponse(const QString&);
    void parseLocalitiesResponse(const QString&);


    bool active() const;
    bool error() const;
    bool noPermission() const;
    QString errorMessage() const;
    QString currentLocalityName() const;

    QVariantMap countryModel() const;
    PagedDataModel* localitiesModel() const;

private:
    AbstractPane *homeSource;

    Page *rootSource;
    ActivityIndicator* m_ActivityIndicator;
    ActivityIndicator* m_ContentIndicator;
    bool m_active;
    bool m_error;
    QString m_errorMessage;
    QString m_countryCode;
    QVariantMap m_countryModel;
    PagedDataModel* m_localitiesModel;
    QString m_currentLocalityName;

    ListView* m_ListView;

    bool loadingMore;

    bool m_noPermission;

};


#endif

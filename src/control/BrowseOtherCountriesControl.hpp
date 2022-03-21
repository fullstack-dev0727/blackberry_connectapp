/*
 * Copyright UBT Global.
 *
 *  Created on: 04 Mar 2016
 *      Author: Lucas Bento
 */

#ifndef BROWSEOTHERCOUNTRIESCONTROL_HPP
#define BROWSEOTHERCOUNTRIESCONTROL_HPP

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
#include "../custom/BaseControl.h"
using namespace bb::cascades;

/**
 * This class deals mainly with Contacting UBT
 */

class BrowseOtherCountriesControl: public BaseControl
{
Q_OBJECT

Q_PROPERTY(bb::cascades::DataModel* m_countriesModel READ countriesModel NOTIFY countriesChanged )

public:
    BrowseOtherCountriesControl(QObject *parent = 0);
    void setHomeSource(AbstractPane *root = 0);
    static void openCountryInfo(AbstractPane *homeSource, QString code, QString name);
    void setRoot(Page *root = 0);

public Q_SLOTS:
    void openAction(QString id);
    void requestCountries();
    void openCountry(QString code, QString name);
    void reset();

    bb::cascades::DataModel* countriesModel() const;

Q_SIGNALS:
    void activeChanged();
    void statusChanged();
    void currentUserChanged();
    void countriesChanged();

private Q_SLOTS:
    /*
     * Handles the complete signal from countries request when
     * the request is complete
     */
    void onCountriesResponse(const QString &info, bool success);
private:
    /*
     * Parses the JSON response
     */
    void parseCountriesResponse(const QString&);

    bool active() const;
    bool error() const;
    QString errorMessage() const;

private:
    AbstractPane *homeSource;

    Page *rootSource;
    ActivityIndicator* m_ActivityIndicator;
    ActivityIndicator* m_ContentIndicator;
    bool m_active;
    bool m_error;
    QString m_errorMessage;
    QString m_countryCode;
    bb::cascades::GroupDataModel* m_countriesModel;

    ListView* m_ListView;

    bool loadingMore;

    bool m_noPermission;

};

#endif

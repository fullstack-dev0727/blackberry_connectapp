/*
 * Copyright UBT Global.
 *
 *  Created on: 04 Mar 2016
 *      Author: Lucas Bento
 */

#ifndef COUNTRYCHOOSERCONTROL_HPP
#define COUNTRYCHOOSERCONTROL_HPP


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
#include "../AppSettings.hpp"
#include "HomeControl.hpp"
#include "../custom/BaseControl.h"
using namespace bb::cascades;

/**
 * This class deals mainly with Contacting UBT
 */

class CountryChooserControl : public BaseControl
{
    Q_OBJECT

    Q_PROPERTY(bool active READ active NOTIFY activeChanged)
    Q_PROPERTY(bool error READ error NOTIFY statusChanged)
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY statusChanged)
    Q_PROPERTY(QString currentLocalityName READ currentLocalityName NOTIFY currentLocalityNameChanged)


    Q_PROPERTY(bb::cascades::DataModel* m_countriesModel READ countriesModel NOTIFY countriesChanged )

public:
    CountryChooserControl(QObject *parent = 0);
    void setHomeSource(AbstractPane *root = 0);

    void setRoot(Page *root = 0);



public Q_SLOTS:

    void reset();
    Q_INVOKABLE QString dateFromTimestamp(const QString &timestamp);


    void openLocalityChooser(QString code, QString name);

    void requestCountries(bool showAllCountries);
    void requestSetDefaultLocality(QString defaulLocalityId);

    void selectCountry(QString id, QString name);

    bool isDefaultLocality(QString localityId);

Q_SIGNALS:
    void activeChanged();
    void statusChanged();
    void countriesChanged();
    void currentLocalityNameChanged();

    void completedSignal();
    void completed();
private Q_SLOTS:
    /*
     * Handles the complete signal from countries request when
     * the request is complete
     */
    void onRequestCountriesResponse(const QString &info, bool success);
    void onSetDefaultLocalityResponse(const QString &info, bool success);



private:
    /*
     * Parses the JSON response
     */
    void parseCountriesResponse(const QString&);


    bool active() const;
    bool error() const;
    QString errorMessage() const;
    QString currentLocalityName() const;

    bb::cascades::DataModel* countriesModel() const;

private:
    AbstractPane *homeSource;

    Page *rootSource;
    ActivityIndicator* m_ActivityIndicator;
    ActivityIndicator* m_ContentIndicator;
    bool m_active;
    bool m_error;
    bool m_showAllCountries;
    QString m_errorMessage;
    QString m_currentLocalityName;
    bb::cascades::GroupDataModel* m_countriesModel;


    ListView* m_ListView;

};


#endif

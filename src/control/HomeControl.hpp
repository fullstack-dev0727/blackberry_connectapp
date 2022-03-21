/*
 * Copyright UBT Global.
 *
 *  Created on: 01 Feb 2016
 *      Author: Lucas Bento
 */

#ifndef HOMECONTROL_HPP
#define HOMECONTROL_HPP


#include "../AppUi.hpp"
#include <bb/cascades/QListDataModel>
#include <bb/cascades/GroupDataModel>
#include <QtCore/QObject>

#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/NavigationPane>


#include <bb/data/JsonDataAccess>
#include <bb/utility/i18n/RelativeDateFormatter>
#include <bb/cascades/Page>


//Controls
#include "TermsAndConditionsControl.hpp"
#include "ContactControl.hpp"
#include "SearchControl.hpp"
#include "LocalityControl.hpp"
#include "SubdivisionControl.hpp"
#include "HouseholdControl.hpp"
#include "CountryControl.hpp"
#include "CountryChooserControl.hpp"
#include "MyDetailsControl.hpp"
#include "ConnectSyncControl.hpp"
#include "DownloadManager.hpp"

//API Requests
#include "../api/APILoginRequest.hpp"
#include "../api/APIUserRequest.hpp"
#include "../AppSettings.hpp"

//CRUD
#include "../database/CRUDAboutTable.hpp"
#include "../custom/StatusEventHandler.h"
#include "../custom/BaseControl.h"

namespace bb
{
    namespace cascades
    {
        class Page;
        class Container;
    }
}

/**
 * This class deals mainly with the Login to the ConnectAPI.
 */

class HomeControl : public BaseControl
{
    Q_OBJECT

    Q_PROPERTY(bool active READ active NOTIFY activeChanged)
    Q_PROPERTY(bool error READ error NOTIFY statusChanged)

    Q_PROPERTY(QString defaultEmail READ defaultEmail NOTIFY defaultEmailChanged)

    Q_PROPERTY(int homeTopContainerHeight READ homeTopContainerHeight )

    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY statusChanged)

    Q_PROPERTY(QVariant m_loginModel READ loginModel CONSTANT)
    Q_PROPERTY(QVariantMap m_currentUserModel READ currentUserModel NOTIFY currentUserChanged )

    Q_PROPERTY(bb::cascades::DataModel* m_countriesModel READ countriesModel NOTIFY countriesChanged )
    Q_PROPERTY(QString m_pincode READ pinModel WRITE setPinModel NOTIFY pinChanged )
    Q_PROPERTY(QString m_pincode1 READ pinModel1 WRITE setPinModel1 NOTIFY pinChanged1 )
public:

    HomeControl(QObject *parent = 0);
    ~HomeControl();

    void setRoot(AbstractPane *root = 0);
    void showToast(QString message);
    static void openLocalityInfo(AbstractPane *homeSource, QString localityId, QString name);
    static void openCountryInfo(AbstractPane *homeSource, QString code, QString name);
    static void openSubdivisionInfo(AbstractPane *homeSource, QString subdivisionId, QString name);
    static void openHouseholdInfo(AbstractPane *homeSource, QString householdId, QString name);
    static void openUpgradeAccount(AbstractPane *homeSource);

public Q_SLOTS:
    //Verify if logged
    void verifyLogged();
    void loadHomeContent();
    void eraseTokens();

    void checkSync();
    void networkStatusUpdateHandler(bool status, QString type);

    void onTimeFunc();

    bool isExistedPinCode();
    QString getPinCode();
    void setPinCode(QString pinCode);
    bool checkPinCode(QString value);
    QString removeLast(QString data);
    QString append(QString data, QString value);
    int getLength(QString value);
    //Login
    void requestLogin(const QString &username, const QString &password);
    void requestCurrentUser();
    void requestCountries();
    void popScreen();
    void popAll();
    void launchForgotPassword();
    bool isConnectedToInternet();

    bb::cascades::DataModel* countriesModel() const;
    QString pinModel() const;
    QString pinModel1() const;

    void setPinModel(QString value);
    void setPinModel1(QString value);

    //Action Menu
    void openAction(QString id);
    static void openActionItem(AbstractPane *root, QString id, QObject *context);
    void openSheet(QString id);

    //Locality Screen
    void openDefLocality();

    //Country Screen
    void openDefCountry();

    //Select filter by Country
    void selectCountryFilter();

    void openCountry(QString code, QString name);
    void openLocality(QString localityId, QString name);
    void openSubdivision(QString subdivisionId, QString name);
    void openHousehold(QString householdId, QString name);

    void startTimer();
    void stopTimer();

    //void loadFilterBt();
    //void updateFilter(QString name);
    void reset();
    Q_INVOKABLE QString dateFromTimestamp(const QString &timestamp);

    static void offlineSync(bool copyDb, AbstractPane *rootSource, QObject *context);

Q_SIGNALS:
    void openWalkT();
    void loading();
    void logged();
    void enterPin();
    void finished();
    void requestlogin();
    void requestsync();

    void activeChanged();
    void statusChanged();
    void currentUserChanged();
    void countriesChanged();
    void defaultEmailChanged();
    void pinChanged();
    void pinChanged1();
private Q_SLOTS:
    /*
     * Handles the complete signal from LoginRequest when
     * the request is complete
     * @see LoginRequest::complete()
     */
    void onLogin(const QString &info, bool success);


    /*
     * Handles the complete signal from UserRequest when
     * the request is complete
     */
    void onCurrentUserResponse(const QString &info, bool success);

    /*
     * Handles the complete signal from countries request when
     * the request is complete
     */
    void onCountriesResponse(const QString &info, bool success);


private:
    /*
     * Parses the JSON response
     */
    void parseLoginResponse(const QString&);
    void parseCurrentUserResponse(const QString&);
    void parseCountriesResponse(const QString&);

    int homeTopContainerHeight() const;
    int homeBottomContainerHeight() const;
    bool active() const;
    bool error() const;
    QString errorMessage() const;
    QString defaultEmail() const;
    QString hashedPinCode(QString pinCode);

    QVariant loginModel() const;
    QVariantMap currentUserModel() const;

private:
    static const char *FEEDBACK_URL;
    static const char *FORGOT_PASSWORD_URL;
    AbstractPane *rootSource;
    bool m_active;
    bool m_error;
    QString m_errorMessage;
    QVariant m_loginModel;
    QString m_defaultEmail;
    int m_homeTopContainerHeight;
    int m_homeBottomContainerHeight;

    QTimer* timer;
    QVariantMap m_currentUserModel;
    bb::cascades::GroupDataModel* m_countriesModel;
    QString m_pincode;
    QString m_pincode1;
    StatusEventHandler* statusEventHandler;
};

#endif

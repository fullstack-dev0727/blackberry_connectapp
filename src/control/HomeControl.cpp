/*
 * Copyright UBT Global.
 *
 *  Created on: 01 Feb 2016
 *      Author: Lucas Bento
 */

#include "HomeControl.hpp"
#include "../AppUi.hpp"
#include "../database/SQLiteUtil.hpp"
#include <bb/cascades/Container>
#include <bb/cascades/Label>
#include <bb/system/SystemToast>
#include <bb/system/SystemUiPosition>
#include <bb/system/phone/Phone>
#include <bb/cascades/Sheet>
#include <QFile>
#include <QNetworkConfigurationManager>
#include <QNetworkConfiguration>
#include <bb/cascades/Sheet>

using namespace bb::cascades;
using namespace bb::data;
using namespace bb::system;

const char *HomeControl::FEEDBACK_URL = "https://app.smartsheet.com/b/form?EQBCT=5453eb5c087a4198bbc96ff816fde492";
const char *HomeControl::FORGOT_PASSWORD_URL = "http://52.62.201.188/#/forgotpassword";


HomeControl::HomeControl(QObject *parent)
: BaseControl()
, m_active(false)
, m_error(false)
, rootSource(0)
, m_loginModel(QVariant())
, m_currentUserModel(QVariantMap())
, m_countriesModel(new GroupDataModel(QStringList() << "Name"))

{
    m_countriesModel->setGrouping(ItemGrouping::None);
    m_defaultEmail = AppSettings::getUserEmail();
    statusEventHandler = new StatusEventHandler();

    isConnectedToInternet();
}
HomeControl::~HomeControl()
{
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    if (isConnectedToInternet()) {
        AppSettings::setLastOnlineTime(currentTime);
    }
    stopTimer();
}
void HomeControl::startTimer() {
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    AppSettings::setFirstIdleTime(currentTime);

    timer = new QTimer(this);
    timer->start(5000);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(onTimeFunc()));
}
void HomeControl::stopTimer() {
    timer->stop();
}
void HomeControl::onTimeFunc() {
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    if (currentTime - AppSettings::getFirstIdleTime() > 1000 * 60 * 15) {
         emit enterPin();
         stopTimer();
    }
}
void HomeControl::networkStatusUpdateHandler(bool status, QString type) {
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    AppSettings::setLastOnlineTime(currentTime);
}
void HomeControl::checkSync() {

    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    qint64 lastOnlineTime = AppSettings::getLastOnlineTime();
    if (lastOnlineTime != 0) {
        qint64 offsetTime = currentTime - lastOnlineTime;
        if (offsetTime > 30 * 24 * 3600 * 1000) { // more than 30 days
            SQLiteUtil::wipeDb();
            AppSettings::setLastOnlineTime(currentTime);
        }
    }
    connect(statusEventHandler,
            SIGNAL(networkStatusUpdated(bool, QString)),
            this,
            SLOT(networkStatusUpdateHandler(bool, QString)));


    if (AppSettings::getFirstAccess()) {
        offlineSync(true, rootSource, this);
    }else  {
        //checkDatabaseHasChanged
        qint64 millisecondsDiff = 172800000; //2 days
        if (SQLiteUtil::openConnection()) {

            CRUDAboutTable mCRUDAboutTable;
            if (CRUDBase::databaseVersion() != mCRUDAboutTable.getVersion()) {
                offlineSync(true, rootSource, this);
            }
            else if (mCRUDAboutTable.getLastUpdatedDateTime().msecsTo(QDateTime::currentDateTime()) > millisecondsDiff) { //sync every 2 days
                 offlineSync(false, rootSource, this);
            }
            else {
                loadHomeContent();
            }
        }else { //Database failed to open
            offlineSync(true, rootSource, this); //Try to fix it
        }


    }

    startTimer();
}


void HomeControl::verifyLogged()
{
    if (!isConnectedToInternet()) {
        showToast("Please connect to the internet");
        emit requestlogin();
        return;
    }
    if (AppSettings::getToken().isEmpty() || AppSettings::getToken().isNull())
        emit requestlogin();
    else {
        //Get User  and close login screen
        emit logged();
    }
}
bool HomeControl::checkPinCode(QString value) {
    if (value != "" && hashedPinCode(value) == getPinCode())
        return true;
    return false;
}
QString HomeControl::getPinCode() {
    return AppSettings::getPinCode();
}
void HomeControl::setPinCode(QString pinCode) {
    AppSettings::setPinCode(hashedPinCode(pinCode));
}

QString HomeControl::hashedPinCode(QString pinCode) {
    QByteArray pinArray = QCryptographicHash::hash(pinCode.toLatin1(), QCryptographicHash::Md5);
    QString md5Pin = QString::fromUtf8(pinArray);
    return md5Pin;
}
bool HomeControl::isExistedPinCode() {
    QString pinCode = AppSettings::getPinCode();
    if (pinCode == "")
        return false;
    return true;
}
QString HomeControl::removeLast(QString data) {
    if (data.size() == 0)
        return data;
    return data.remove(data.size() - 1, 1);
}
QString HomeControl::append(QString data, QString value) {
    return data.append(value);
}
int HomeControl::getLength(QString value) {
    return value.size();
}
void HomeControl::setPinModel(QString value) {
    m_pincode = value;
}
void HomeControl::setPinModel1(QString value) {
    m_pincode1 = value;
}
void HomeControl::loadHomeContent()
{
    //Load user and countries if global subs
    //if dialog not showing, open it
    requestCurrentUser();
}

//void HomeControl::loadFilterBt()
//{
//    updateFilter(AppSettings::getCountryFilterName());
//
//}


void HomeControl::reset()
{
    m_error = false;
    m_errorMessage.clear();

    emit statusChanged();
}

void HomeControl::eraseTokens()
{
    AppSettings::setToken("");
    AppSettings::setRefreshToken("");
    AppSettings::setCountryFilterCode("");
    AppSettings::setCountryFilterName("");

}


void HomeControl::setRoot(AbstractPane *root)
{
    rootSource = root;
    qDebug() << "Class: HomeControl.cpp";

}

void HomeControl::launchForgotPassword() {
    navigator_invoke(FORGOT_PASSWORD_URL, NULL);
}

bool HomeControl::isConnectedToInternet() {
    return APIUtil::isConnectedToInternet();
}

//-------------------------------------------------------
//-----------------LOGIN REQUEST-------------------------------------
//-------------------------------------------------------


/*
 *  HomeControl::requestLogin(const QString &username,const QString &password)
 *
 */
void HomeControl::requestLogin(const QString &username,const QString &password)
{
    if (m_active)
        return;
    m_errorMessage = "";
    m_error = false;
    emit statusChanged();

    //if (isLogged()) {
    //    emit logged();
    //    return;
    //}


    if (username.isEmpty() || password.isEmpty()) {
        m_errorMessage = "Please enter a valid username and password";
        m_error = true;
        emit statusChanged();
        return;
        emit finished();

    }
    if (!isConnectedToInternet()) {
        showToast("Please connect to the internet");
        return;
    }

    APILoginRequest* request = new APILoginRequest(this);
    bool ok = connect(request, SIGNAL(sigLoginResponse(QString, bool)), this, SLOT(onLogin(QString, bool)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
    request->requestToken(username, password);


    AppSettings::setUserEmail(username);

    m_active = true;
    emit activeChanged();
}

/*
 * LoginControl::onLogin(const QString &info, bool success)
 * Called when login finished
 */
void HomeControl::onLogin(const QString &info, bool success)
{
    APILoginRequest *request = qobject_cast<APILoginRequest*>(sender());

    //qDebug() << info;
    if (success) {
        parseLoginResponse(info);

        QString t = m_loginModel.toMap().value("access_token").toString();
        //save
        AppSettings::setToken(m_loginModel.toMap().value("access_token").toString());
        AppSettings::setRefreshToken(m_loginModel.toMap().value("refresh_token").toString());

        //Get User info before open the app
        emit logged();


    } else {
        JsonDataAccess dataAccess;
        QVariant err = dataAccess.loadFromBuffer(info);
        m_errorMessage = err.toMap().value("error_description").toString();
        m_error = true;
        emit statusChanged();
        emit finished();
    }

    m_active = false;
    emit activeChanged();

    request->deleteLater();
}

/*
 * LoginControl::parseResponse()
 *
 * Parses the JSON data
 */
void HomeControl::parseLoginResponse(const QString &response)
{
    m_loginModel.clear();

    if (response.trimmed().isEmpty())
        return;

    // Parse the json response with JsonDataAccess
    JsonDataAccess dataAccess;
    m_loginModel = dataAccess.loadFromBuffer(response);
}


//-------------------------------------------------------
//-----------------LOGIN REQUEST-------------------------------------
//-------------------------------------------------------



//-------------------------------------------------------
//-----------------USER REQUEST-------------------------------------
//-------------------------------------------------------


/*
 *  HomeControl::requestCurrentUser(const QString &username,const QString &password)
 *
 */
void HomeControl::requestCurrentUser()
{

    emit loading();

    APIUserRequest* request = new APIUserRequest(this);

    bool ok = connect(request, SIGNAL(sigCurrentUserResponse(QString, bool)), this, SLOT(onCurrentUserResponse(QString, bool)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
    request->requestCurrentUser();


}

/*
 * LoginControl::onLogin(const QString &info, bool success)
 * Called when login finished
 */
void HomeControl::onCurrentUserResponse(const QString &info, bool success)
{
    APIUserRequest *request = qobject_cast<APIUserRequest*>(sender());



    if (success) {
        parseCurrentUserResponse(info);


        //Save user Locals

        //qDebug() << "Current df locality: " + m_currentUserModel["DefaultLocality"].toMap().value("Id").toString();

        AppSettings::setUserCountryCode(m_currentUserModel["DefaultCountry"].toMap().value("Code").toString());
        AppSettings::setUserLocalityCode(m_currentUserModel["DefaultLocality"].toMap().value("Id").toString());
        AppSettings::setUserLocalityName(m_currentUserModel["DefaultLocality"].toMap().value("Name").toString());
        AppSettings::setCurrentUserId(m_currentUserModel.value("Id").toString());
        AppSettings::setCurrentUserHouseholdId(m_currentUserModel.value("Member").toMap().value("Householder").toMap().value("Id").toString());
        AppSettings::setCurrentUserManageSubsLink(m_currentUserModel.value("DefaultCountry").toMap().value("ConnectConfig").toMap().value("ManageSubscriptionLink").toString());



        m_countriesModel->clear();
        m_countriesModel->insert(m_currentUserModel);
        //List of countries
        const QVariantMap subscription = m_currentUserModel["Subscription"].toMap();
        const QVariantList subscribedCountries = subscription["SubscribedCountries"].toList();
        QString subsC = "";

        int qt = 0;
        foreach (const QVariant &country, subscribedCountries) {
            qt++;
            const QVariantMap countryMap = country.toMap();

            m_countriesModel->insert(countryMap);

            QString s = " \"" + countryMap["Code"].toString() + "\"";
            if (!subsC.isEmpty())
                subsC = subsC + ",";
            subsC = subsC +  s;
        }

        //Save subscribed countries
        AppSettings::setCurrentUserSubscribedCountries(subsC);
        AppSettings::setCurrentUserSubscribedCountriesQt(qt);


        //TODO  - RESOLUTION / 2
        m_homeTopContainerHeight = 700;

        //TODO  - countries * 50
        m_homeBottomContainerHeight = 1700;

        emit countriesChanged();
        emit currentUserChanged();



        //if first access, show walkthorugh
        if (AppSettings::getFirstAccess())
            emit openWalkT();





    }else if (info.compare("loginRequest") == 0) {

        emit finished();

        //emit requestlogin();
        QMetaObject::invokeMethod(rootSource, "openLogin");

    }

    request->deleteLater();



}

/*emit log
 * HomeControl::parseResponse()
 *
 * Parses the JSON data
 */
void HomeControl::parseCurrentUserResponse(const QString &response)
{
    m_currentUserModel.clear();


    if (response.trimmed().isEmpty())
        return;

    // Parse the json response with JsonDataAccess
    JsonDataAccess dataAccess;
    m_currentUserModel = dataAccess.loadFromBuffer(response).toMap();


    QString test = m_currentUserModel.value("Email").toString();
    QString test1 = m_currentUserModel.value("Id").toString();
    //m_currentUserModel->insert(variant);

}


//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//-----------------USER REQUEST-------------------------------------
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


//-------------------------------------------------------
//-----------------COUNTRIES REQUEST-------------------------------------
//-------------------------------------------------------


/*
 *  HomeControl::requestCountries()
 *
 */
void HomeControl::requestCountries()
{

    APICountriesRequest* request = new APICountriesRequest(this);
    bool ok = connect(request, SIGNAL(sigCountriesResponse(QString, bool)), this, SLOT(onCountriesResponse(QString, bool)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
    request->reqCountries(1, false, "");

}

/*
 * LoginControl::onLogin(const QString &info, bool success)
 * Called when login finished
 */
void HomeControl::onCountriesResponse(const QString &info, bool success)
{
    APICountriesRequest *request = qobject_cast<APICountriesRequest*>(sender());

    if (success) {
        parseCountriesResponse(info);

        emit countriesChanged();


    }else if (info.compare("loginRequest") == 0) {

        //emit requestlogin();
        QMetaObject::invokeMethod(rootSource, "openLogin");

    }

    request->deleteLater();
}

/*
 * HomeControl::parseResponse()
 *
 * Parses the JSON data
 */
void HomeControl::parseCountriesResponse(const QString &response)
{
    m_countriesModel->clear();


    if (response.trimmed().isEmpty())
        return;

    // Parse the json response with JsonDataAccess
    JsonDataAccess dataAccess;

    const QVariantMap variant = dataAccess.loadFromBuffer(response).toMap();
    // The qvariant is a map of searches which is extracted as a list
    const QVariantList searchResults = variant["Results"].toList();

    // For each object in the array, push the variantmap in its raw form
    // into the ListView
    foreach (const QVariant &artifact, searchResults) {
        if (artifact.toMap().value("Code").toString().compare("ZZ") != 0) //Ignore All Countries (ZZ)
            m_countriesModel->insert(artifact.toMap());
    }



}


//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//-----------------COUNTRIES REQUEST-------------------------------------
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx



//-------------------------------------------------------
//-----------------OPEN ACTION ITEM-------------------------------------
//-------------------------------------------------------

void HomeControl::openAction(QString id)
{
    openActionItem(rootSource, id, this);
}

/*
 * HomeControl::openActionItem()
 *
 * Manage the action Items actions
 */
void HomeControl::openActionItem(AbstractPane *root, QString id, QObject *context)
{
    if (id.compare("homeAction") == 0) {
        HomeControl* homeControl = new HomeControl();
        homeControl->setRoot(root);
        homeControl->popAll();
    } else if (id.compare("searchAction") == 0) {
        QmlDocument *qml = QmlDocument::create("asset:///DetailScreens/SearchScreen.qml");

        //Expose TermsAndConditiions control  to qml
        SearchControl *searchControl = new SearchControl();
        searchControl->setHomeSource(root);

        qml->setContextProperty("_control", searchControl);
        qml->setContextProperty("_home", root);

        Page *page = qml->createRootObject<Page>();

        searchControl->setRoot(page);

        NavigationPane* m_navigationPane = root->findChild<NavigationPane*>(QString("homeNavigation"));
        m_navigationPane->push(page);
    } else if (id.compare("detailsAction") == 0) {
        QmlDocument *qml = QmlDocument::create("asset:///DetailScreens/MyDetailsScreen.qml");

        //Expose TermsAndConditiions control  to qml
        MyDetailsControl *myDetailsControl = new MyDetailsControl();
        myDetailsControl->setHomeSource(root);

        qml->setContextProperty("_control", myDetailsControl);
        qml->setContextProperty("_home", root);

        Page *page = qml->createRootObject<
                Page>();

        myDetailsControl->setRoot(page);
        myDetailsControl->requestHousehold();  //Get data

        NavigationPane* m_navigationPane = root->findChild<NavigationPane*>(QString("homeNavigation"));
        m_navigationPane->push(page);


    } else if (id.compare("locationAction") == 0) {

        QmlDocument *qml = QmlDocument::create("asset:///DetailScreens/DefaultLocalityChooser.qml");

        CountryChooserControl *countryChooserControl = new CountryChooserControl();
        countryChooserControl->setHomeSource(root);

        qml->setContextProperty("_control", countryChooserControl);
        qml->setContextProperty("_home", root);

        Page *page = qml->createRootObject<
                Page>();

        countryChooserControl->setRoot(page);
        countryChooserControl->requestCountries(false);  //Get data

        NavigationPane* m_navigationPane = root->findChild<NavigationPane*>(QString("homeNavigation"));
        m_navigationPane->push(page);

    } else if (id.compare("termsAction") == 0) {
        QmlDocument *qml = QmlDocument::create("asset:///DetailScreens/TermsAndConditionsScreen.qml");

        //Expose TermsAndConditiions control  to qml
        TermsAndConditionsControl *termsAndConditionsControl = new TermsAndConditionsControl();
        termsAndConditionsControl->setHomeSource(root);
        qml->setContextProperty("_control", termsAndConditionsControl);
        qml->setContextProperty("_home", root);

        Page *page = qml->createRootObject<Page>();

        termsAndConditionsControl->setRoot(page);
        NavigationPane* m_navigationPane = root->findChild<NavigationPane*>(QString("homeNavigation"));
        m_navigationPane->push(page);
        QTimer::singleShot(500, termsAndConditionsControl, SLOT(requestTerms()));

    } else if (id.compare("contactAction") == 0) {
        QmlDocument *qml = QmlDocument::create("asset:///DetailScreens/ContactScreen.qml");

        //Expose Contact control  to qml
        ContactControl *contactControl = new ContactControl();
        contactControl->setHomeSource(root);
        qml->setContextProperty("_control", contactControl);
        qml->setContextProperty("_home", root);


        Page *page = qml->createRootObject<Page>();

        contactControl->setRoot(page);
        contactControl->requestContactInfo();  //Get data

        NavigationPane* m_navigationPane = root->findChild<NavigationPane*>(QString("homeNavigation"));
        m_navigationPane->push(page);


    } else if (id.compare("feedbackAction") == 0) {
        navigator_invoke(FEEDBACK_URL, NULL);
    } else if (id.compare("syncAction") == 0) {
        offlineSync(false, root, context);
    }

}


void HomeControl::openSheet(QString id)
{
    if (id.compare("terms") == 0) {

        QmlDocument* qml = QmlDocument::create("asset:///DetailScreens/TermsAndConditionsScreenSheet.qml");
        //Expose TermsAndConditiions control  to qml
        TermsAndConditionsControl *termsAndConditionsControl = new TermsAndConditionsControl();
        termsAndConditionsControl->setHomeSource(rootSource);
        qml->setContextProperty("_control", termsAndConditionsControl);
        qml->setContextProperty("_home", rootSource);

        Sheet* root = qml->createRootObject<Sheet>();

        termsAndConditionsControl->setRoot(root);
        root->open();
        QTimer::singleShot(500, termsAndConditionsControl, SLOT(requestTerms()));
    }

}

//-------------------------------------------------------
//-----------------OPEN LOCALITY DEF-------------------------------------
//-------------------------------------------------------

/*
 * HomeControl::openDefLocality()
 *
 * Open the default locality screen when buttons is clicked
 */
void HomeControl::openDefLocality()
{

    openLocality(m_currentUserModel.value("DefaultLocality").toMap().value("Id").toString(), m_currentUserModel.value("DefaultLocality").toMap().value("Name").toString());


}

//-------------------------------------------------------
//-----------------OPEN COUNTRY DEF-------------------------------------
//-------------------------------------------------------

/*
 * HomeControl::openDefCountry()
 *
 * Open the default country screen when buttons is clicked
 */
void HomeControl::openDefCountry()
{

    openCountry( m_currentUserModel.value("DefaultCountry").toMap().value("Code").toString(), m_currentUserModel.value("DefaultCountry").toMap().value("Name").toString());

}

/*
 * HomeControl::selectCountryFilter()
 *
 * Open the default country selection to use as a filter
 */
void HomeControl::selectCountryFilter()
{
    QmlDocument *qml = QmlDocument::create("asset:///DetailScreens/CountryChooser.qml");

    //Expose Locality control  to qml
    CountryChooserControl *countryChooserControl = new CountryChooserControl();
    countryChooserControl->setHomeSource(rootSource);

    qml->setContextProperty("_control", countryChooserControl);
    qml->setContextProperty("_main", this);


    Page *page = qml->createRootObject<Page>();

    countryChooserControl->setRoot(page);
    countryChooserControl->requestCountries(true);  //Get data

    NavigationPane* m_navigationPane = rootSource->findChild<NavigationPane*>(QString("homeNavigation"));
    m_navigationPane->push(page);
}



//-------------------------------------------------------
//-----------------OPEN PAGES-------------------------------------
//-------------------------------------------------------


void HomeControl::openLocality(QString localityId, QString localityName)
{
    openLocalityInfo(rootSource, localityId, localityName);
}

void HomeControl::openLocalityInfo(AbstractPane *homeSource, QString localityId, QString localityName)
{
    QmlDocument *qml = QmlDocument::create("asset:///DetailScreens/LocalityScreen.qml");

    //Expose Locality control  to qml
    LocalityControl *localityControl = new LocalityControl();
    localityControl->setHomeSource(homeSource);

    qml->setContextProperty("_control", localityControl);
    qml->setContextProperty("_home", homeSource);
    //Locality Id and Name
    qml->setProperty("_localityId", localityId);
    qml->setProperty("_localityName", localityName);


    Page *page = qml->createRootObject<Page>();

    localityControl->setRoot(page);

    NavigationPane* m_navigationPane = homeSource->findChild<NavigationPane*>(QString("homeNavigation"));
    m_navigationPane->push(page);

    localityControl->requestLocality(localityId);  //Get data


}

void HomeControl::openCountry(QString code, QString name)
{
    openCountryInfo(rootSource, code, name);
}
/*
 * HomeControl::openCountryInfo(QString code)
 *
 * Open the country screen when buttons is clicked
 */
void HomeControl::openCountryInfo(AbstractPane *homeSource, QString code, QString name)
{

    QmlDocument *qml = QmlDocument::create("asset:///DetailScreens/CountryScreen.qml");

    //Expose Locality control  to qml
    CountryControl *countryControl = new CountryControl();
    countryControl->setHomeSource(homeSource);
    qml->setContextProperty("_control", countryControl);
    qml->setContextProperty("_home", homeSource);

    //Locality Id and Name
    qml->setProperty("_countryCode", code);
    qml->setProperty("_countryName", name);

    Page *page = qml->createRootObject<Page>();

    countryControl->setRoot(page);

    NavigationPane* m_navigationPane = homeSource->findChild<NavigationPane*>(QString("homeNavigation"));
    m_navigationPane->push(page);

    countryControl->requestCountry(code);  //Get data
}

void HomeControl::openSubdivision(QString subdivisionId, QString name)
{
    openSubdivisionInfo(rootSource, subdivisionId, name);
}
/*
 * HomeControl::openSubdivisionInfo(AbstractPane *homeSource, QString subdivisionId, QString name)
 *
 * Open the subdivision screen when buttons is clicked
 */
void HomeControl::openSubdivisionInfo(AbstractPane *homeSource, QString subdivisionId, QString name)
{
    QmlDocument *qml = QmlDocument::create("asset:///DetailScreens/SubdivisionScreen.qml");

    //Expose Locality control  to qml
    SubdivisionControl *subdivisionControl = new SubdivisionControl();
    subdivisionControl->setHomeSource(homeSource);
    qml->setContextProperty("_control", subdivisionControl);
    qml->setContextProperty("_home", homeSource);

    subdivisionControl->id = subdivisionId;

    Page *page = qml->createRootObject<Page>();

    subdivisionControl->setRoot(page);

    NavigationPane* m_navigationPane = homeSource->findChild<NavigationPane*>(QString("homeNavigation"));
    m_navigationPane->push(page);

    subdivisionControl->load();
    //subdivisionControl->requestSubdivision(subdivisionId);  //Get data
}

void HomeControl::openHousehold(QString householdId, QString name)
{
    openHouseholdInfo(rootSource, householdId, name);
}
/*
 * HomeControl::openHouseholdInfo(AbstractPane *homeSource, QString householdId, QString name)
 *
 * Open the household screen when buttons is clicked
 */
void HomeControl::openHouseholdInfo(AbstractPane *homeSource, QString householdId, QString name)
{

    QmlDocument *qml = QmlDocument::create("asset:///DetailScreens/HouseholdScreen.qml");

    //Expose household control  to qml
    HouseholdControl *householdControl = new HouseholdControl();
    householdControl->setHomeSource(homeSource);
    qml->setContextProperty("_control", householdControl);
    qml->setContextProperty("_home", homeSource);
    //Locality Id and Name
    qml->setProperty("_householdId", householdId);
    qml->setProperty("_householdName", name);

    Page *page = qml->createRootObject<Page>();

    householdControl->setRoot(page);

    NavigationPane* m_navigationPane = homeSource->findChild<NavigationPane*>(QString("homeNavigation"));
    m_navigationPane->push(page);

    householdControl->requestHousehold(householdId);  //Get data
}

void HomeControl::openUpgradeAccount(AbstractPane *homeSource)
{

    QmlDocument *qml = QmlDocument::create("asset:///DetailScreens/UpgradeAccount.qml");

    //Expose household control  to qml
    Page *page = qml->createRootObject<Page>();

    NavigationPane* m_navigationPane = homeSource->findChild<NavigationPane*>(QString("homeNavigation"));
    m_navigationPane->push(page);

}


void HomeControl::popScreen()
{
    NavigationPane* m_navigationPane = rootSource->findChild<NavigationPane*>(QString("homeNavigation"));
    m_navigationPane->pop();
}

void HomeControl::popAll()
{
    if (rootSource) {
        NavigationPane* m_navigationPane = rootSource->findChild<NavigationPane*>(QString("homeNavigation"));
        int count = m_navigationPane->count();
        for (int i = 1; i < count; i++) {
            m_navigationPane->pop();
        }
    }
}

bool HomeControl::active() const
{
    return m_active;
}

bool HomeControl::error() const
{
    return m_error;
}

int HomeControl::homeTopContainerHeight() const
{
    return m_homeTopContainerHeight ;
}

int HomeControl::homeBottomContainerHeight() const
{
    return m_homeTopContainerHeight ;
}


QString HomeControl::errorMessage() const
{
    return m_errorMessage;
}

QString HomeControl::defaultEmail() const
{
    return m_defaultEmail;
}

//void HomeControl::updateFilter(QString name)
//{
//    Label* m_FilterButton = rootSource->findChild<Label*>(QString("btCountryFilter"));
//    if (!name.isNull() && !name.isEmpty())
//        m_FilterButton->setText(name);
//    else
//        m_FilterButton->setText("All countries");
//
//}

QString HomeControl::dateFromTimestamp(const QString &timestamp) {
    QDateTime date;
    date.setMSecsSinceEpoch(timestamp.toLongLong());
    return date.toString();
}

QVariant HomeControl::loginModel() const
{
    return m_loginModel;
}

QVariantMap HomeControl::currentUserModel() const
{
    return m_currentUserModel;
}

bb::cascades::DataModel* HomeControl::countriesModel() const
{
    return m_countriesModel;
}
QString HomeControl::pinModel() const
{
    return m_pincode;
}
QString HomeControl::pinModel1() const
{
    return m_pincode1;
}
void HomeControl::offlineSync(bool copyDb, AbstractPane *rootSource, QObject *context) {
    QmlDocument *qml = QmlDocument::create("asset:///DetailScreens/SyncDataScreen.qml");

    //Expose sync control  to qml
    ConnectSyncControl *mConnectSyncControl = new ConnectSyncControl(context);
    if (copyDb)
        mConnectSyncControl->replaceDb = true;

    bool ok = connect(mConnectSyncControl, SIGNAL(loadMainUser()), context, SLOT(requestCurrentUser()));

    mConnectSyncControl->setHomeSource(rootSource);
    qml->setContextProperty("_control", mConnectSyncControl);
    qml->setContextProperty("_home", rootSource);

    Page *page = qml->createRootObject<Page>();
    mConnectSyncControl->setRoot(page);

    Sheet* pMySheet = Sheet::create()
                      .content(page)
                      .open();

    mConnectSyncControl->setSheet(pMySheet);

    //NavigationPane* m_navigationPane = rootSource->findChild<NavigationPane*>(QString("homeNavigation"));
    //m_navigationPane->push(page);

    //emit requestsync();
}

void HomeControl::showToast(QString message)
{
    SystemToast* m_toast = new SystemToast();

    m_toast->setBody(message);
    m_toast->setPosition(SystemUiPosition::MiddleCenter);
    m_toast->show();
}


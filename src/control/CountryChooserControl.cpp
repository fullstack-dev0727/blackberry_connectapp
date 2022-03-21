/*
 * Copyright UBT Global.
 *
 *  Created on: 04 Mar 2016
 *      Author: Lucas Bento
 */

#include "CountryChooserControl.hpp"


using namespace bb::cascades;
using namespace bb::data;

CountryChooserControl::CountryChooserControl(QObject *parent)
: BaseControl()
, m_active(false)
, m_error(false)
, homeSource(0)
, rootSource(0)
, m_countriesModel(new GroupDataModel(QStringList() << "Name"))
, m_ActivityIndicator(0)
, m_ContentIndicator(0)
, m_ListView(0)
{

    m_countriesModel->setGrouping(ItemGrouping::None);
    m_showAllCountries = true;
}

void CountryChooserControl::reset()
{
    m_error = false;
    m_errorMessage.clear();

    emit countriesChanged();
}

void CountryChooserControl::setHomeSource(AbstractPane *root)
{
    homeSource = root;
}

void CountryChooserControl::setRoot(Page *root)
{
    rootSource = root;
    qDebug() << "Class: CountryChooserControl.cpp";

    m_ListView  = rootSource->findChild<ListView*>(QString("country_listview"));
    m_ListView->resetDataModel();
    m_ListView->setDataModel(m_countriesModel);

    m_currentLocalityName = AppSettings::getUserLocalityName();
    emit currentLocalityNameChanged();

}





//-------------------------------------------------------
//-----------------COUNTRIES REQUEST-------------------------------------
//-------------------------------------------------------


/*
 *  CountryChooserControl::requestCountries()
 *
 */
void CountryChooserControl::requestCountries(bool showAllCountries)
{
    m_ContentIndicator  = rootSource->findChild<ActivityIndicator*>(QString("contentLoadingIndicator"));

    m_showAllCountries = showAllCountries;

    //Start Loading indicator
    m_ContentIndicator->start();


    APICountriesRequest* request = new APICountriesRequest(this);
    bool ok = connect(request, SIGNAL(sigCountriesResponse(QString, bool)), this, SLOT(onRequestCountriesResponse(QString, bool)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
    request->reqCountries(1, showAllCountries, "");
}

/*
 * CountryChooserControl::onRequestCountriesResponse(const QString &info, bool success)
 * Called when Countries request finished
 */
void CountryChooserControl::onRequestCountriesResponse(const QString &info, bool success)
{
    APICountriesRequest *request = qobject_cast<APICountriesRequest*>(sender());

    if (success) {

        parseCountriesResponse(info);

        emit countriesChanged();

    }else if (info.compare("loginRequest") == 0) {

        //emit requestlogin();
        QMetaObject::invokeMethod(homeSource, "openLogin");

    }


    m_ContentIndicator->stop();

    if (request)
        request->deleteLater();
}

/*
 * CountryControl::parseLocalitiesResponse()
 *
 * Parses the JSON data
 */
void CountryChooserControl::parseCountriesResponse(const QString &response) {
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
    bool first = true;
    foreach (const QVariant &artifact, searchResults) {
            m_countriesModel->insert(artifact.toMap());
    }

}


//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//-----------------COUNTRIES REQUEST-------------------------------------
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


//-------------------------------------------------------
//-----------------SET DEFAULT LOCALITY REQUEST-------------------------------------
//-------------------------------------------------------


void CountryChooserControl::requestSetDefaultLocality(QString defaulLocalityId)
{

    APIUserRequest* request = new APIUserRequest(this);
    bool ok = connect(request, SIGNAL(sigSetDefaultLocalityResponse(QString, bool)), this, SLOT(onSetDefaultLocalityResponse(QString, bool)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
    request->setDefaultLocality(defaulLocalityId, AppSettings::getCurrentUserId());

}


void CountryChooserControl::onSetDefaultLocalityResponse(const QString &info, bool success)
{
    APIUserRequest *request = qobject_cast<APIUserRequest*>(sender());

    qDebug() << info;
    if (success) {


        //Get current user again?
        //requestCurrentUser();
        emit completedSignal();

        emit completed();


        NavigationPane* m_navigationPane = homeSource->findChild<NavigationPane*>(QString("homeNavigation"));
        m_navigationPane->pop();
        m_navigationPane->pop();



        //Save user Locals

        //AppSettings::setUserCountryCode(m_currentUserModel["DefaultCountry"].toMap().value("Code").toString());
        //AppSettings::setUserLocalityCode(locality);

    }else if (info.compare("loginRequest") == 0) {

        emit completed();
        //emit requestlogin();
        QMetaObject::invokeMethod(rootSource, "openLogin");

    }

    emit completed();
    request->deleteLater();
}



//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//-----------------SET DEFAULT LOCALITY REQUEST-------------------------------------
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


void CountryChooserControl::selectCountry(QString id, QString name) {

    if (!id.isNull()) {

        AppSettings::setCountryFilterCode(id);
        AppSettings::setCountryFilterName(name);

        //Close chooser
        NavigationPane* m_navigationPane = homeSource->findChild<NavigationPane*>(QString("homeNavigation"));
        m_navigationPane->pop();
    }

}



void CountryChooserControl::openLocalityChooser(QString code, QString name) {
    if (!code.isNull()) {
        QmlDocument *qml = QmlDocument::create("asset:///DetailScreens/DefaultLocalityChooserLoc.qml");

        //Expose Locality control  to qml
        CountryControl *countryControl = new CountryControl();
        countryControl->setHomeSource(homeSource);
        qml->setContextProperty("_control", countryControl);
        qml->setContextProperty("_countrychooser", this);
        qml->setContextProperty("_home", homeSource);

        //Locality Id and Name
        qml->setProperty("_countryCode", code);
        qml->setProperty("_countryName", name);



        Page *page = qml->createRootObject<Page>();

        countryControl->setRoot(page);
        countryControl->requestCountry(code);  //Get data

        NavigationPane* m_navigationPane = homeSource->findChild<NavigationPane*>(QString("homeNavigation"));
        m_navigationPane->push(page);

        emit currentLocalityNameChanged();

    }
}



bool CountryChooserControl::active() const
{
    return m_active;
}

bool CountryChooserControl::error() const
{
    return m_error;
}

QString CountryChooserControl::errorMessage() const
{
    return m_errorMessage;
}

QString CountryChooserControl::currentLocalityName() const
{
    return m_currentLocalityName;
}

bool CountryChooserControl::isDefaultLocality(QString localityId)
{
    if (localityId == AppSettings::getUserLocalityCode())
        return true;
    else
        return false;
}

QString CountryChooserControl::dateFromTimestamp(const QString &timestamp) {
    QDateTime date;
    date.setMSecsSinceEpoch(timestamp.toLongLong());
    return date.toString();
}


bb::cascades::DataModel* CountryChooserControl::countriesModel() const
{
    return m_countriesModel;
}


/*
 * Copyright UBT Global.
 *
 *  Created on: 04 Mar 2016
 *      Author: Lucas Bento
 */

#include "BrowseOtherCountriesControl.hpp"
#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/NavigationPane>
#include <bb/cascades/ListScrollStateHandler>
#include <bps/navigator.h>

using namespace bb::cascades;
using namespace bb::data;

BrowseOtherCountriesControl::BrowseOtherCountriesControl(QObject *parent)
: BaseControl()
, m_active(false)
, m_error(false)
, m_noPermission(false)
, homeSource(0)
, rootSource(0)
, m_countriesModel(new GroupDataModel(QStringList() << "Name"))
, m_ActivityIndicator(0)
, m_ContentIndicator(0)
{
    m_countriesModel->setGrouping(ItemGrouping::None);
    loadingMore = false;

}

void BrowseOtherCountriesControl::reset()
{
    m_error = false;
    m_errorMessage.clear();

    emit countriesChanged();
}

void BrowseOtherCountriesControl::openAction(QString id)
{
    HomeControl::openActionItem(homeSource, id, this);
}

void BrowseOtherCountriesControl::setHomeSource(AbstractPane *root)
{
    homeSource = root;
}

void BrowseOtherCountriesControl::setRoot(Page *root)
{
    rootSource = root;

    qDebug() << "Class: BrowseOtherCountriesControl.cpp";

}



//-------------------------------------------------------
//-----------------COUNTRY REQUEST-------------------------------------
//-------------------------------------------------------



void BrowseOtherCountriesControl::requestCountries()
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
void BrowseOtherCountriesControl::onCountriesResponse(const QString &info, bool success)
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
void BrowseOtherCountriesControl::parseCountriesResponse(const QString &response)
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


void BrowseOtherCountriesControl::openCountry(QString code, QString name)
{
    openCountryInfo(homeSource, code, name);
}
/*
 * BrowseOtherCountriesControl::openCountryInfo(QString code)
 *
 * Open the country screen when buttons is clicked
 */
void BrowseOtherCountriesControl::openCountryInfo(AbstractPane *homeSource, QString code, QString name)
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






bool BrowseOtherCountriesControl::active() const
{
    return m_active;
}

bool BrowseOtherCountriesControl::error() const
{
    return m_error;
}


QString BrowseOtherCountriesControl::errorMessage() const
{
    return m_errorMessage;
}

bb::cascades::DataModel* BrowseOtherCountriesControl::countriesModel() const
{
    return m_countriesModel;
}


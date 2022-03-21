/*
 * Copyright UBT Global.
 *
 *  Created on: 04 Mar 2016
 *      Author: Lucas Bento
 */

#include "CountryControl.hpp"
#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/NavigationPane>
#include <bb/cascades/ListScrollStateHandler>
#include <bps/navigator.h>

using namespace bb::cascades;
using namespace bb::data;

CountryControl::CountryControl(QObject *parent)
: BaseControl()
, m_active(false)
, m_error(false)
, m_noPermission(false)
, homeSource(0)
, rootSource(0)
, m_countryModel(QVariantMap())
, m_localitiesModel(new PagedDataModel(parent))
, m_ActivityIndicator(0)
, m_ContentIndicator(0)
, m_ListView(0)
{
    //m_localitiesModel->setGrouping(ItemGrouping::None);
    loadingMore = false;

}

void CountryControl::manageSubs()
{
    QString url = AppSettings::getCurrentUserManageSubsLink();
    navigator_invoke(url.toStdString().c_str(), 0);
}

void CountryControl::reset()
{
    m_error = false;
    m_errorMessage.clear();

    emit countryChanged();
}

void CountryControl::setHomeSource(AbstractPane *root)
{
    homeSource = root;
}

void CountryControl::setRoot(Page *root)
{
    rootSource = root;

    qDebug() << "Class: CountryControl.cpp";

    m_ListView  = rootSource->findChild<ListView*>(QString("country_listview"));
    m_ListView->resetDataModel();
    m_ListView->setDataModel(m_localitiesModel);
    //Infinite Scroll
    ListScrollStateHandler::create(m_ListView).onAtEndChanged(this, SLOT(onAtEndChanged(bool)));

    m_currentLocalityName = AppSettings::getUserLocalityName();
    emit currentLocalityNameChanged();

}


void CountryControl::openAction(QString id)
{
    HomeControl::openActionItem(homeSource, id, this);
}

void CountryControl::onAtEndChanged(bool atEnd)
{

    if ((m_localitiesModel->size()-1) > 0) {
        int page = ((m_localitiesModel->size()-1) / APIUtil::pageSize);
        float pg = ((float)m_localitiesModel->size()-1) / (float)APIUtil::pageSize;
        if ((float)pg - (float)page > (float)0)
            page++;

        if (!loadingMore && atEnd && (m_localitiesModel->size()-1) >= (APIUtil::pageSize*page)) { //Make sure it just tries to load when there are more items

            loadingMore = true;
            //simulate pressing the load more button.

            page++;
            requestLocalities(m_countryCode, page);
        }
    }

}


void CountryControl::browseOtherCountries() {

    QmlDocument *qml = QmlDocument::create("asset:///DetailScreens/BrowseOtherCountriesScreen.qml");

    //Expose control  to qml
    BrowseOtherCountriesControl *control = new BrowseOtherCountriesControl();
    control->setHomeSource(homeSource);
    qml->setContextProperty("_control", control);
    qml->setContextProperty("_home", homeSource);



    Page *page = qml->createRootObject<Page>();

    control->setRoot(page);

    NavigationPane* m_navigationPane = homeSource->findChild<NavigationPane*>(QString("homeNavigation"));
    m_navigationPane->push(page);

    control->requestCountries();  //Get data
}
//-------------------------------------------------------
//-----------------COUNTRY REQUEST-------------------------------------
//-------------------------------------------------------


void CountryControl::requestCountry(QString countryCode)
{
    m_countryCode = countryCode;

    m_ActivityIndicator  = rootSource->findChild<ActivityIndicator*>(QString("actLoadingIndicator"));

    //Start Loading indicator
    m_ActivityIndicator->start();


    APICountriesRequest* request = new APICountriesRequest(this);
    bool ok = connect(request, SIGNAL(sigCountryResponse(QString, bool)), this, SLOT(onCountryResponse(QString, bool)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
    request->requestCountry(countryCode);
}

/*
 * LocalityControl::onLocalityResponse(const QString &info, bool success)
 * Called when locality request finished
 */
void CountryControl::onCountryResponse(const QString &info, bool success)
{
    APICountriesRequest *request = qobject_cast<APICountriesRequest*>(sender());

    if (success) {
        parseCountryResponse(info);

        emit countryChanged();

        //Show main content
        m_localitiesModel->clear();
        m_localitiesModel->append(m_countryModel); //main
        emit localitiesChanged();

    }else if (info.compare("loginRequest") == 0) {

        //emit requestlogin();
        QMetaObject::invokeMethod(homeSource, "openLogin");

    } else if (info.contains("no_permission")) {
        m_noPermission = true;
        emit noPermissionChanged();
    }

    m_ActivityIndicator->stop();

    if (request)
        request->deleteLater();
}

/*
 * LocalityControl::parseResponse()
 *
 * Parses the JSON data
 */
void CountryControl::parseCountryResponse(const QString &response)
{
    m_countryModel.clear();


    if (response.trimmed().isEmpty())
        return;

    // Parse the json response with JsonDataAccess
    JsonDataAccess dataAccess;
    m_countryModel = dataAccess.loadFromBuffer(response).toMap();



}


//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//-----------------COUNTRY REQUEST-------------------------------------
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx



//-------------------------------------------------------
//-----------------LOCALITIES REQUEST-------------------------------------
//-------------------------------------------------------


/*
 *  CountryControl::requestLocalities(QString countryCode)
 *
 */
void CountryControl::requestLocalities(QString countryCode, int page)
{
    m_ContentIndicator  = rootSource->findChild<ActivityIndicator*>(QString("contentLoadingIndicator"));

    //Start Loading indicator
    m_ContentIndicator->start();


    APILocalitiesRequest* request = new APILocalitiesRequest(this);
    bool ok = connect(request, SIGNAL(sigLocalitiesResponse(QString, bool)), this, SLOT(onRequestLocalitiesResponse(QString, bool)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
    request->requestLocalities(page, countryCode, "");
}

/*
 * CountryControl::onLocalitiesResponse(const QString &info, bool success)
 * Called when Localities request finished
 */
void CountryControl::onRequestLocalitiesResponse(const QString &info, bool success)
{
    APILocalitiesRequest *request = qobject_cast<APILocalitiesRequest*>(sender());

    if (success) {
        parseLocalitiesResponse(info);

        emit localitiesChanged();

    }else if (info.compare("loginRequest") == 0) {

        //emit requestlogin();
        QMetaObject::invokeMethod(homeSource, "openLogin");

    }


    m_ContentIndicator->stop();

    if (request)
        request->deleteLater();
    loadingMore = false;
}

/*
 * CountryControl::parseLocalitiesResponse()
 *
 * Parses the JSON data
 */
void CountryControl::parseLocalitiesResponse(const QString &response)
{

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
        m_localitiesModel->append(artifact.toMap());
    }




}


//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//-----------------LOCALITIES REQUEST-------------------------------------
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


void CountryControl::openLocality(QString localityId, QString localityName)
{
    HomeControl::openLocalityInfo(homeSource, localityId, localityName);
}







bool CountryControl::active() const
{
    return m_active;
}

bool CountryControl::error() const
{
    return m_error;
}

bool CountryControl::noPermission() const
{
    return m_noPermission;
}

QString CountryControl::errorMessage() const
{
    return m_errorMessage;
}

QString CountryControl::currentLocalityName() const
{
    return m_currentLocalityName;
}

QString CountryControl::dateFromTimestamp(const QString &timestamp) {
    QDateTime date;
    date.setMSecsSinceEpoch(timestamp.toLongLong());
    return date.toString();
}

QVariantMap CountryControl::countryModel() const
{
    return m_countryModel;
}

PagedDataModel* CountryControl::localitiesModel() const
{
    return m_localitiesModel;
}


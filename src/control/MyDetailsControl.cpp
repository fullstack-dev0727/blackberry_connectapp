/*
 * Copyright UBT Global.
 *
 *  Created on: 19 May 2016
 *      Author: Lucas Bento
 */

#include "MyDetailsControl.hpp"
#include "../api/APIUserRequest.hpp"
#include "../AppSettings.hpp"
#include <bps/navigator.h>

using namespace bb::cascades;
using namespace bb::data;

MyDetailsControl::MyDetailsControl(QObject *parent)
    : BaseControl()
    , m_active(false)
    , m_error(false)
    , m_mydetails(new ImageItem())
    , m_familyUpdates(false)
    , m_photoUpdates(false)
{

}

void MyDetailsControl::reset()
{
    m_error = false;
    m_errorMessage.clear();

    emit myDetailsChanged();
}

void MyDetailsControl::manageSubs()
{
    QString url = AppSettings::getCurrentUserManageSubsLink();
    navigator_invoke(url.toStdString().c_str(), 0);
}

void MyDetailsControl::setHomeSource(AbstractPane *root)
{
    homeSource = root;
}

void MyDetailsControl::setRoot(Page *root)
{
    rootSource = root;
    qDebug() << "Class: MyDetailsControl.cpp";
}

//-------------------------------------------------------
//-----------------HOUSEHOLD REQUEST-------------------------------------
//-------------------------------------------------------

/*
 *  MyDetailsControl::requestHousehold(QString householdId)
 *
 */
void MyDetailsControl::requestHousehold()
{

    QString m_householdId = AppSettings::getCurrentUserHouseholdId(); //
    if (m_active)
        return;

    //Start Loading indicator
    m_ActivityIndicator = rootSource->findChild<ActivityIndicator*>(QString("actLoadingIndicator"));
    m_ActivityIndicator->start();

    APIHouseholdsRequest* request = new APIHouseholdsRequest(this);
    bool ok = connect(request, SIGNAL(sigHouseholdResponse(QString, bool)), this,
            SLOT(onHouseholdResponse(QString, bool)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
    request->requestHousehold(m_householdId);

    m_active = true;
    emit activeChanged();
}

/*
 * MyDetailsControl::onHouseholdResponse(const QString &info, bool success)
 * Called when household request finished
 */
void MyDetailsControl::onHouseholdResponse(const QString &info, bool success)
{
    APIHouseholdsRequest *request = qobject_cast<APIHouseholdsRequest*>(sender());

    if (success) {
        qDebug() << "household response:" + info;

        QStringList list = info.split("\n");
        for (int i = 0; i < list.length(); i++) {
            qDebug() << list[i];
        }

        parseHouseholdResponse(info);

        emit myDetailsChanged();

        //Get image
        m_mydetails->load();

    } else if (info.compare("loginRequest") == 0) {

        //emit requestlogin();
        QMetaObject::invokeMethod(homeSource, "openLogin");

    } else {
        m_errorMessage = info;
        m_error = true;
        emit statusChanged();
    }

    m_active = false;
    m_ActivityIndicator->stop();
    emit activeChanged();

    request->deleteLater();
}

/*
 * MyDetailsControl::parseResponse()
 *
 * Parses the JSON data
 */
void MyDetailsControl::parseHouseholdResponse(const QString &response)
{

    if (response.trimmed().isEmpty())
        return;

    // Parse the json response with JsonDataAccess
    JsonDataAccess dataAccess;
    QVariantMap resp = dataAccess.loadFromBuffer(response).toMap();
    m_mydetails = new ImageItem(resp.value("Photo").toMap().value("SignedURL720").toString(), resp,
            this);
    // TODO: assign correct values from API
//    m_familyUpdates = true;
//    m_photoUpdates = true;
//    m_displayWorkPhone = true;
//    m_displayMobilePhone = true;
//Householder.Email
//    m_address = m_mydetails->itemData().value("FormattedAddress");
//    m_homePhone = m_mydetails->itemData().value("HomePhone");
//    m_workPhone = m_mydetails->itemData().value("WorkPhone");
//    m_mobilePhone = m_mydetails->itemData().value("MobilePhone");
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//-----------------HOUSEHOLD REQUEST-------------------------------------
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

//-------------------------------------------------------
//-----------------DETAILS REQUEST-------------------------------------
//-------------------------------------------------------

/*
 void MyDetailsControl::requestMyDetails()
 {
 if (m_active)
 return;

 //Start Loading indicator
 m_ActivityIndicator  = rootSource->findChild<ActivityIndicator*>(QString("contentLoadingIndicator"));
 m_ActivityIndicator->start();

 APICountryConfigRequest* request = new APICountryConfigRequest(this);
 bool ok = connect(request, SIGNAL(sigCountryConfigResponse(QString, bool)), this, SLOT(onContactInfoResponse(QString, bool)));
 Q_ASSERT(ok);
 Q_UNUSED(ok);
 request->requestCountryConfig();

 m_active = true;
 emit activeChanged();
 }


 void MyDetailsControl::onMyDetailsResponse(const QString &info, bool success)
 {
 APICountryConfigRequest *request = qobject_cast<APICountryConfigRequest*>(sender());

 if (success) {
 parseContactInfoResponse(info);

 //update
 emit ctScreenStatusChanged();

 }else if (info.compare("loginRequest") == 0) {

 //emit requestlogin();
 QMetaObject::invokeMethod(homeSource, "openLogin");

 } else {
 m_errorMessage = info;
 m_error = true;
 emit statusChanged();
 }

 m_active = false;
 m_ActivityIndicator->stop();
 emit activeChanged();

 request->deleteLater();
 }


 void MyDetailsControl::parseMyDetailsResponse(const QString &response)
 {
 m_ContactInfo.clear();

 if (response.trimmed().isEmpty())
 return;

 // Parse the json response with JsonDataAccess
 JsonDataAccess dataAccess;
 m_ContactInfo = dataAccess.loadFromBuffer(response).toMap();
 }


 //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
 //-----------------CONTACT INFO REQUEST-------------------------------------
 //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

 */

//-------------------------------------------------------
//-----------------SEND CHANGE REQUEST-------------------------------------
//-------------------------------------------------------

void MyDetailsControl::sendChangeRequest()
{

    QVariantMap changes;

    //TODO - GET THE RIGHT VALUES
    //changes["EmailAddress"] = values.value("Email");
    //changes["Locality"] = values.value("Locality").toMap().value("Name");
    //changes["Subdivision"] = values.value("Subdivision");
    changes["Address"] = m_mydetails->itemData().value("FormattedAddress");
    changes["Landline"] = m_mydetails->itemData().value("HomePhone");
    changes["WorkNumber"] = m_mydetails->itemData().value("WorkPhone");
    changes["MobileNumber"] = m_mydetails->itemData().value("MobilePhone");
    changes["FamilyUpdates"] = familyUpdates();
    changes["PhotoUpdates"] = photoUpdates();
    changes["DisplayWorkPhone"] = displayWorkPhone();
    changes["DisplayMobilePhone"] = displayMobilePhone();
    changes["Comments"] = comments(); //values.value("Comments");

    for (QVariantMap::const_iterator iter = changes.begin(); iter != changes.end(); ++iter) {
        qDebug() << iter.key() << iter.value();
    }

    APIUserRequest* request = new APIUserRequest(this);
    bool ok = connect(request, SIGNAL(sigSendChangeResquestResponse(QString, bool)), this,
            SLOT(onSendChangeRequestResponse(QString, bool)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
    request->changeReq(changes);

}

/*
 * ContractControl::onSentEmailResponse(const QString &info, bool success)
 * Called when contact email has been sent
 */
void MyDetailsControl::onSendChangeRequestResponse(const QString &info, bool success)
{
    APIUserRequest *request = qobject_cast<APIUserRequest*>(sender());

    //TODO - CLOSE even IF IT'S WAS NOT SUCCESSFUL
    emit changeRequestSent();

    if (success) {
        //update
        //emit changeRequestSent();

    } else if (info.compare("loginRequest") == 0) {

        //emit requestlogin();
        QMetaObject::invokeMethod(homeSource, "openLogin");

    } else {
        m_errorMessage = info;
        m_error = true;
        emit statusChanged();
    }

    request->deleteLater();
}

/*
 * ContractControl::parseResponse()
 *
 * Parses the JSON data
 */
void MyDetailsControl::parseSendChangeRequestResponse(const QString &response)
{

    if (response.trimmed().isEmpty())
        return;

    // Parse the json response with JsonDataAccess
    JsonDataAccess dataAccess;
    //m_ContactInfo = dataAccess.loadFromBuffer(response).toMap();
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//-----------------SEND EMAIL REQUEST-------------------------------------
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

bool MyDetailsControl::familyUpdates() const
{
    return m_familyUpdates;
}

bool MyDetailsControl::photoUpdates() const
{
    return m_photoUpdates;
}
bool MyDetailsControl::displayWorkPhone() const
{
    return m_displayWorkPhone;
}

bool MyDetailsControl::displayMobilePhone() const
{
    return m_displayMobilePhone;
}

QString MyDetailsControl::comments() const
{
    return m_comments;
}
QString MyDetailsControl::emailAddress() const
{
    return m_emailAddress;
}
QString MyDetailsControl::address() const
{
    return m_address;
}
QString MyDetailsControl::workPhone() const
{
    return m_workPhone;
}
QString MyDetailsControl::homePhone() const
{
    return m_homePhone;
}
QString MyDetailsControl::mobilePhone() const
{
    return m_mobilePhone;
}
bool MyDetailsControl::active() const
{
    return m_active;
}
void MyDetailsControl::setComments(QString comment) {
    m_comments = comment;
}
void MyDetailsControl::setEmailAddress(QString email_address) {
    m_emailAddress = email_address;
}
void MyDetailsControl::setAddress(QString address) {
    m_address = address;
}
void MyDetailsControl::setPhotoUpdates(bool photoUpdates) {
    m_photoUpdates = photoUpdates;
}
void MyDetailsControl::setFamilyUpdates(bool familyUpdates) {
    m_familyUpdates = familyUpdates;
}
void MyDetailsControl::setDisplayWorkPhone(bool displayWorkPhone) {
    m_displayWorkPhone = displayWorkPhone;
}
void MyDetailsControl::setDisplayMobilePhone(bool displayMobilePhone) {
    m_displayMobilePhone = displayMobilePhone;
}
void MyDetailsControl::setWorkPhone(QString work_phone) {
    m_workPhone = work_phone;
}
void MyDetailsControl::setMobilePhone(QString mobile_phone) {
    m_mobilePhone = mobile_phone;
}
void MyDetailsControl::setHomePhone(QString home_phone) {
    m_homePhone = home_phone;
}

bool MyDetailsControl::error() const
{
    return m_error;
}

QString MyDetailsControl::errorMessage() const
{
    return m_errorMessage;
}

QString MyDetailsControl::dateFromTimestamp(const QString &timestamp)
{
    QDateTime date;
    date.setMSecsSinceEpoch(timestamp.toLongLong());
    return date.toString();
}

ImageItem* MyDetailsControl::myDetails() const
{
    return m_mydetails;
}


/*
 * Copyright UBT Global.
 *
 *  Created on: 22 Feb 2016
 *      Author: Lucas Bento
 */

#include "ContactControl.hpp"
#include "../api/APICountryConfigRequest.hpp"
#include "../AppSettings.hpp"
#include <bb/system/phone/Phone>

using namespace bb::cascades;
using namespace bb::data;

ContactControl::ContactControl(QObject *parent)
    : BaseControl()
    , m_active(false)
    , m_error(false)
    , m_ContactInfo(QVariantMap())
{

}

void ContactControl::reset()
{
    m_error = false;
    m_errorMessage.clear();

    emit ctScreenStatusChanged();
}

void ContactControl::setHomeSource(AbstractPane *root)
{
    homeSource = root;
}

void ContactControl::setRoot(Page *root)
{
    rootSource = root;
    qDebug() << "Class: ContactControl.cpp";
}


void ContactControl::setUserInfo(QString userId, QString userName) {
    m_userId = userId;
    m_userName = userName;

    emit userInfoChanged();
}

//-------------------------------------------------------
//-----------------CONTACT INFO REQUEST-------------------------------------
//-------------------------------------------------------


/*
 *  TermsAndConditionsControl::requestLogin(const QString &username,const QString &password)
 *
 */
void ContactControl::requestContactInfo()
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

/*
 * LoginControl::onLogin(const QString &info, bool success)
 * Called when login finished
 */
void ContactControl::onContactInfoResponse(const QString &info, bool success)
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

/*
 * LoginControl::parseResponse()
 *
 * Parses the JSON data
 */
void ContactControl::parseContactInfoResponse(const QString &response)
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



//-------------------------------------------------------
//-----------------SEND CONTACT EMAIL REQUEST-------------------------------------
//-------------------------------------------------------


/*
 *  ContractControl::sendUserEmail(const QString userId, const QString &subject, const QString &body)
 *
 */
void ContactControl::sendUserEmail(const QString userId, const QString &subject, const QString &body)
{



    APICountryConfigRequest* request = new APICountryConfigRequest(this);
    bool ok = connect(request, SIGNAL(sigContactEmailResponse(QString, bool)), this, SLOT(onSentEmailResponse(QString, bool)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
    request->sendCtcEmail(userId, subject, body);


}

/*
 *  ContractControl::sendContactEmail(const QString &subject, const QString &body)
 *
 */
void ContactControl::sendContactEmail(const QString &subject, const QString &body)
{



    APICountryConfigRequest* request = new APICountryConfigRequest(this);
    bool ok = connect(request, SIGNAL(sigContactEmailResponse(QString, bool)), this, SLOT(onSentEmailResponse(QString, bool)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
    request->sendCtcEmail("", subject, body);


}

/*
 * ContractControl::onSentEmailResponse(const QString &info, bool success)
 * Called when contact email has been sent
 */
void ContactControl::onSentEmailResponse(const QString &info, bool success)
{
    APICountryConfigRequest *request = qobject_cast<APICountryConfigRequest*>(sender());

    if (success) {
        //update
        emit ctMessageSent();

    }else if (info.compare("loginRequest") == 0) {

        //emit requestlogin();
        QMetaObject::invokeMethod(homeSource, "openLogin");

    } else {
        m_errorMessage = info;
        m_error = true;
        emit statusChanged();
    }

    emit ctFinished();

    request->deleteLater();
}

/*
 * ContractControl::parseResponse()
 *
 * Parses the JSON data
 */
void ContactControl::parseSentEmailResponse(const QString &response)
{
    m_ContactInfo.clear();

    if (response.trimmed().isEmpty())
        return;

    // Parse the json response with JsonDataAccess
    JsonDataAccess dataAccess;
    m_ContactInfo = dataAccess.loadFromBuffer(response).toMap();
}


//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//-----------------SEND CONTACT EMAIL REQUEST-------------------------------------
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx




bool ContactControl::active() const
{
    return m_active;
}

bool ContactControl::error() const
{
    return m_error;
}

QString ContactControl::errorMessage() const
{
    return m_errorMessage;
}

QString ContactControl::userName() const
{
    return m_userName;
}

QString ContactControl::userId() const
{
    return m_userId;
}


QString ContactControl::dateFromTimestamp(const QString &timestamp) {
    QDateTime date;
    date.setMSecsSinceEpoch(timestamp.toLongLong());
    return date.toString();
}

QVariantMap ContactControl::contactInfo() const
{
    return m_ContactInfo;
}

void ContactControl::tCallNumber(QString number) {
    bb::system::phone::Phone phone;
    phone.initiateCellularCall(number);
}





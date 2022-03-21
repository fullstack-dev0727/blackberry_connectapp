/*
 * Copyright UBT Global.
 *
 *  Created on: 01 Feb 2016
 *      Author: Lucas Bento
 */

#include "TermsAndConditionsControl.hpp"
#include "../api/APICountryConfigRequest.hpp"
#include "../AppSettings.hpp"
#include "../database/SQLiteUtil.hpp"

using namespace bb::cascades;
using namespace bb::data;

TermsAndConditionsControl::TermsAndConditionsControl(QObject *parent)
: BaseControl()
, m_active(false)
, m_error(false)
, m_termsnConditions(QVariantMap())
{
    sheetSource = 0;
    rootSource = 0;
}

void TermsAndConditionsControl::reset()
{
    m_error = false;
    m_errorMessage.clear();

    emit tncScreenStatusChanged();
}

void TermsAndConditionsControl::setHomeSource(AbstractPane *root)
{
    homeSource = root;
}


void TermsAndConditionsControl::setRoot(Page *root)
{
    rootSource = root;
    qDebug() << "Class: TermsAndConditionsControl.cpp";
}

void TermsAndConditionsControl::setRoot(Sheet *root)
{
    sheetSource = root;
}
//-------------------------------------------------------
//-----------------TERMS REQUEST-------------------------------------
//-------------------------------------------------------

TermsWorker::TermsWorker(TermsAndConditionsControl * control) {
    termsControl = control;
}
/*
 *  TermsAndConditionsControl::requestLogin(const QString &username,const QString &password)
 *
 */
void TermsAndConditionsControl::requestTerms()
{
    if (m_active)
        return;

    //Start Loading indicator
    if (sheetSource)
        m_ActivityIndicator  = sheetSource->findChild<ActivityIndicator*>(QString("contentLoadingIndicator"));
    else if (rootSource)
        m_ActivityIndicator  = rootSource->findChild<ActivityIndicator*>(QString("contentLoadingIndicator"));


    if (m_ActivityIndicator)
        m_ActivityIndicator->start();

    TermsWorker* termsWorker = new TermsWorker(this);
    QThread* thread = new QThread();
    termsWorker->moveToThread(thread);
    connect(thread, SIGNAL(started()), termsWorker, SLOT(handleTerms()));
    thread->start();
}

void TermsWorker::handleTerms() {
    APICountryConfigRequest* request = new APICountryConfigRequest(this);
    bool ok = connect(request, SIGNAL(sigCountryConfigResponse(QString, bool)), termsControl, SLOT(onTermsAndConditionsResponse(QString, bool)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
    request->requestCountryConfig();
    termsControl->m_active = true;
}
/*
 * LoginControl::onLogin(const QString &info, bool success)
 * Called when login finished
 */
void TermsAndConditionsControl::onTermsAndConditionsResponse(const QString &info, bool success)
{
    APICountryConfigRequest *request = qobject_cast<APICountryConfigRequest*>(sender());

    if (success) {
        parseTermsAndConditionsResponse(info);
        //open app
        emit tncScreenStatusChanged();

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

    if (request)
        request->deleteLater();
}

/*
 * LoginControl::parseResponse()
 *
 * Parses the JSON data
 */
void TermsAndConditionsControl::parseTermsAndConditionsResponse(const QString &response)
{
    if (response.trimmed().isEmpty())
        return;
    m_termsnConditions.clear();
    // Parse the json response with JsonDataAccess
    JsonDataAccess dataAccess;
    m_termsnConditions = dataAccess.loadFromBuffer(response).toMap();
}


//-------------------------------------------------------
//-----------------LOGIN REQUEST-------------------------------------
//-------------------------------------------------------

bool TermsAndConditionsControl::active() const
{
    return m_active;
}

bool TermsAndConditionsControl::error() const
{
    return m_error;
}

QString TermsAndConditionsControl::errorMessage() const
{
    return m_errorMessage;
}

QString TermsAndConditionsControl::dateFromTimestamp(const QString &timestamp) {
    QDateTime date;
    date.setMSecsSinceEpoch(timestamp.toLongLong());
    return date.toString();
}

QVariantMap TermsAndConditionsControl::termsnConditions() const
{
    return m_termsnConditions;
}




/*
m_contentModel * Copyright UBT Global.
 *
 *  Created on: 03 Mar 2016
 *      Author: Lucas Bento
 */

#include "HouseholdControl.hpp"
#include "HomeControl.hpp"
#include "../imgutil/imageitem.hpp"
#include <bb/platform/MapInvoker>
#include <bb/system/phone/Phone>
#include <QtCore/QTime>
#include <bps/navigator.h>

using namespace bb::cascades;
using namespace bb::data;


HouseholdControl::HouseholdControl(QObject *parent)
: BaseControl()
, m_active(false)
, m_error(false)
, m_hdImage(false)
, m_noPermission(false)
, m_householdModel(QVariantMap())
//, m_membersModel(new GroupDataModel(QStringList() << "LastName"))
, m_contentModel(new QListDataModel<QObject*>())
{
    //m_membersModel->setGrouping(ItemGrouping::None);
}

void HouseholdControl::manageSubs()
{
    QString url = AppSettings::getCurrentUserManageSubsLink();
    navigator_invoke(url.toStdString().c_str(), 0);
}

void HouseholdControl::reset()
{
    m_error = false;
    m_errorMessage.clear();

    emit householdChanged();
}


void HouseholdControl::setHomeSource(AbstractPane *root)
{
    homeSource = root;
}

void HouseholdControl::setRoot(Page *root)
{
    rootSource = root;
    qDebug() << "Class: HouseholdControl.cpp";

    m_ListView  = rootSource->findChild<ListView*>(QString("members_listview"));
    m_ListView->resetDataModel();
    m_ListView->setDataModel(m_contentModel);


}

void HouseholdControl::openAction(QString id)
{
    HomeControl::openActionItem(homeSource, id, this);
}



//-------------------------------------------------------
//-----------------HOUSEHOLD REQUEST-------------------------------------
//-------------------------------------------------------


/*
 *  HouseholdControl::requestHousehold(QString householdId)
 *
 */
void HouseholdControl::requestHousehold(QString householdId)
{
    //Request first from datrabase
    m_ActivityIndicator  = rootSource->findChild<ActivityIndicator*>(QString("actLoadingIndicator"));

    m_householdId = householdId;
    if (m_active)
        return;


    //Start Loading indicator
    m_ActivityIndicator->start();


    APIHouseholdsRequest* request = new APIHouseholdsRequest(this);
    bool ok = connect(request, SIGNAL(sigHouseholdResponse(QString, bool)), this, SLOT(onHouseholdResponse(QString, bool)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
    request->requestHousehold(householdId);

    m_active = true;
    emit activeChanged();
}

/*
 * HouseholdControl::onHouseholdResponse(const QString &info, bool success)
 * Called when household request finished
 */
void HouseholdControl::onHouseholdResponse(const QString &info, bool success)
{
    APIHouseholdsRequest *request = qobject_cast<APIHouseholdsRequest*>(sender());

    if (success) {
        m_contentModel->clear();

        parseHouseholdResponse(info);

        //emit contentChanged();
        emit householdChanged();

        requestMembers();

        m_hdImage = true;
        emit hdImageChanged();
        emit contentChanged();


    }else if (info.compare("loginRequest") == 0) {

        //emit requestlogin();
        QMetaObject::invokeMethod(homeSource, "openLogin");

    } else if (info.contains("no_permission")) {
        m_noPermission = true;
        emit noPermissionChanged();
    } else {
        m_errorMessage = info;
        m_error = true;
        emit statusChanged();
    }

    if (m_ActivityIndicator)
        m_ActivityIndicator->stop();

    m_active = false;
    emit activeChanged();

    if (request)
        request->deleteLater();
}

/*
 * HouseholdControl::parseResponse()
 *
 * Parses the JSON data
 */
void HouseholdControl::parseHouseholdResponse(const QString &response)
{
    m_householdModel.clear();


    if (response.trimmed().isEmpty())
        return;

    // Parse the json response with JsonDataAccess
    JsonDataAccess dataAccess;
    m_householdModel = dataAccess.loadFromBuffer(response).toMap();

    m_contentModel->append(new ImageItem(m_householdModel.value("Photo").toMap().value("SignedURL340").toString(), m_householdModel, this));

    //load house hold pict
    //qobject_cast<ImageItem*>(m_contentModel->value(0))->load();
}


//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//-----------------HOUSEHOLD REQUEST-------------------------------------
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx



//-------------------------------------------------------
//-----------------MEMBERS REQUEST-------------------------------------
//-------------------------------------------------------


/*
 *  HouseholdControl::requestMembers()
 *
 */
void HouseholdControl::requestMembers()
{

    //Add householders first
    m_contentModel->append(new ImageItem(m_householdModel.value("Householder").toMap().value("PhotoTag").toMap().value("SignedURL").toString(), m_householdModel.value("Householder").toMap(), this));
    if (!m_householdModel.value("HouseholderSpouse").isNull())
        m_contentModel->append(new ImageItem(m_householdModel.value("HouseholderSpouse").toMap().value("PhotoTag").toMap().value("SignedURL").toString(), m_householdModel.value("HouseholderSpouse").toMap(), this));


    const QVariantList searchResults = m_householdModel["FamilyMembers"].toList();


    // For each object in the array, push the variantmap in its raw form
    // into the ListView
    foreach (const QVariant &artifact, searchResults) {
        if (artifact.toMap().value("Householder").toMap().value("Id").toString() == m_householdModel.value("HouseholderId").toString())
            m_contentModel->append(new ImageItem(artifact.toMap().value("PhotoTag").toMap().value("SignedURL").toString(), artifact.toMap(), this));
    }

    foreach (const QVariant &artifact, searchResults) {
        if (artifact.toMap().value("Householder").toMap().value("Id").toString() != m_householdModel.value("HouseholderId").toString())
            m_contentModel->append(new ImageItem(artifact.toMap().value("PhotoTag").toMap().value("SignedURL").toString(), artifact.toMap(), this));
    }

    //add locality
    m_contentModel->append(new ImageItem("", m_householdModel, this));

    //add subdivision
    m_contentModel->append(new ImageItem("", m_householdModel, this));
    emit contentChanged();

    QString log = "Benchmark: 6 - Request members done  " + QTime::currentTime().toString("mm:ss.zzz");
    qDebug() << log;


}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//-----------------MEMBERS REQUEST-------------------------------------
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


void HouseholdControl::tCallNumber(QString number, QString name) {
    m_callDialog = new SystemDialog("Call", "Cancel");

    m_callDialog->setTitle(QString("Calling %1").arg(name));

    m_callDialog->setBody(QString("Phone number: %1").arg(number));
    numberToCall = number;
    bool success = connect(m_callDialog,
            SIGNAL(finished(bb::system::SystemUiResult::Type)),
            this,
            SLOT(onDialogCallFinished(bb::system::SystemUiResult::Type)));

    if (success) {
        m_callDialog->show();
    } else {
        m_callDialog->deleteLater();
    }
}


void HouseholdControl::onDialogCallFinished(bb::system::SystemUiResult::Type type)
{
    if (type == SystemUiResult::ConfirmButtonSelection)
    {
        bb::system::phone::Phone phone;
        phone.initiateCellularCall(numberToCall);
    }
    else {
        qDebug() << "Dialog Rejected";
        // The user rejected the dialog
        m_callDialog->deleteLater();
    }
}

void HouseholdControl::tSendEmail() {
    QmlDocument *qml = QmlDocument::create("asset:///DetailScreens/ContactScreen.qml");

    //Expose Contact control  to qml
    ContactControl *contactControl = new ContactControl();
    contactControl->setHomeSource(homeSource);
    qml->setContextProperty("_control", contactControl);
    qml->setContextProperty("_home", homeSource);


    Page *page = qml->createRootObject<Page>();

    contactControl->setRoot(page);
    contactControl->setUserInfo(m_householdModel.value("Householder").toMap().value("Id").toString(), m_householdModel.value("FirstName").toString() + " " + m_householdModel.value("LastName").toString());

    NavigationPane* m_navigationPane = homeSource->findChild<NavigationPane*>(QString("homeNavigation"));
    m_navigationPane->push(page);
}

void HouseholdControl::openHouseholder(QString householderId) {
    HomeControl::openHouseholdInfo(homeSource, householderId, "");
}


void HouseholdControl::openUpgradeAccount() {
    HomeControl::openUpgradeAccount(homeSource);
}



void HouseholdControl::openLocality(QString localityId) {
    HomeControl::openLocalityInfo(homeSource, localityId, "");
}


void HouseholdControl::openSubdivision(QString subdivisionId) {
    HomeControl::openSubdivisionInfo(homeSource, subdivisionId, "");
}

bool HouseholdControl::active() const
{
    return m_active;
}
bool HouseholdControl::noPermission() const
{
    return m_noPermission;
}

bool HouseholdControl::error() const
{
    return m_error;
}

bool HouseholdControl::hdImage() const
{
    return m_hdImage;
}

QString HouseholdControl::errorMessage() const
{
    return m_errorMessage;
}

QString HouseholdControl::dateFromTimestamp(const QString &timestamp) {
    QDateTime date;
    date.setMSecsSinceEpoch(timestamp.toLongLong());
    return date.toString();
}

QVariantMap HouseholdControl::householdModel() const
{
    return m_householdModel;
}

bb::cascades::DataModel* HouseholdControl::contentModel() const
{
    return m_contentModel;
}

QByteArray HouseholdControl::encodeQString(const QString& toEncode){
    return toEncode.toUtf8();
}


/*
 * Copyright UBT Global.
 *
 *  Created on: 03 Mar 2016
 *      Author: Lucas Bento
 */

#include "LocalityControl.hpp"
#include "../imgutil/imageitem.hpp"
#include <bb/cascades/ListScrollStateHandler>
#include <bps/navigator.h>


using namespace bb::cascades;
using namespace bb::data;

//thread
void LocalityWorker::requestLocality(QString localityId)
{

    APILocalitiesRequest* request = new APILocalitiesRequest(this);
    bool ok = connect(request, SIGNAL(sigLocalityResponse(QString, bool)), this, SLOT(onLocalityResponse(QString, bool)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
    request->requestLocality(localityId);
}


void LocalityWorker::onLocalityResponse(const QString &info, bool success)
{
    APILocalitiesRequest *request = qobject_cast<APILocalitiesRequest*>(sender());

    if (success) {
        //parse
        if (info.trimmed().isEmpty())
            return;

        // Parse the json response with JsonDataAccess
        JsonDataAccess dataAccess;
        QVariant m_localityModel = dataAccess.loadFromBuffer(info);

        emit resultLocalityReady(m_localityModel);

    }else if (info.compare("loginRequest") == 0) {
        emit requestlogin();
    } else if (info.contains("no_permission")) {
        emit noPermission();
    } else {
        emit errorOcurred(info);
    }

    if (request)
        request->deleteLater();
}



/*
 *  LocalityControl::requestHouseholds(int page)
 *
 */
void LocalityWorker::requestHouseholds(int page, QString m_localityId)
{

    APIHouseholdsRequest* request = new APIHouseholdsRequest(this);
    bool ok = connect(request, SIGNAL(sigHouseholdsResponse(QString, bool)), this, SLOT(onRequestHouseholdsResponse(QString, bool)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
    request->requestHouseholdsByLocality(page,  m_localityId);

}

/*
 * LocalityControl::onLocalityResponse(const QString &info, bool success)
 * Called when locality request finished
 */
void LocalityWorker::onRequestHouseholdsResponse(const QString &info, bool success)
{
    APIHouseholdsRequest *request = qobject_cast<APIHouseholdsRequest*>(sender());

    if (success) {
        //Parse
        if (info.trimmed().isEmpty())
            return;


        // Parse the json response with JsonDataAccess
        JsonDataAccess dataAccess;

        const QVariantMap variant = dataAccess.loadFromBuffer(info).toMap();
        // The qvariant is a map of searches which is extracted as a list
        const QVariantList searchResults = variant["Results"].toList();

        emit resultHouseholdsReady(searchResults);


    }else if (info.compare("loginRequest") == 0) {

        emit requestlogin();

    } else {
        emit errorOcurred(info);
    }

    if (request)
        request->deleteLater();
}





/*
 *  :requestSubdivisions()
 *
 */
void LocalityWorker::requestSubdivisions(int page, QString m_localityId)
{

    APISubdivisionsRequest* request = new APISubdivisionsRequest(this);
    bool ok = connect(request, SIGNAL(sigSubdivisionsResponse(QString, bool)), this, SLOT(onRequestSubdivisionsResponse(QString, bool)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
    request->requestSubdivisions(page, m_localityId, "");

}

void LocalityWorker::onRequestSubdivisionsResponse(const QString &info, bool success)
{
    APISubdivisionsRequest *request = qobject_cast<APISubdivisionsRequest*>(sender());

    if (success) {
        //parse
        if (info.trimmed().isEmpty())
            return;

        // Parse the json response with JsonDataAccess
        JsonDataAccess dataAccess;


        const QVariantMap variant = dataAccess.loadFromBuffer(info).toMap();
        // The qvariant is a map of searches which is extracted as a list
        const QVariantList searchResults = variant["Results"].toList();

        emit resultSubdivisionsReady(searchResults);

    }else if (info.compare("loginRequest") == 0) {

        emit requestlogin();

    } else {
        emit errorOcurred(info);
    }

    if (request)
        request->deleteLater();

}



/*
 *  LocalityControl::requestInterchanges()
 *
 */
void LocalityWorker::requestInterchanges(int page, QString m_localityId)
{

    APIInterchangesRequest* request = new APIInterchangesRequest(this);
    bool ok = connect(request, SIGNAL(sigInterchangesResponse(QString, bool)), this, SLOT(onRequestInterchangesResponse(QString, bool)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
    request->requestInterchanges(page, m_localityId, "");

}


void LocalityWorker::onRequestInterchangesResponse(const QString &info, bool success)
{

    APIInterchangesRequest *request = qobject_cast<APIInterchangesRequest*>(sender());

    if (success) {
        //parse
        if (info.trimmed().isEmpty())
            return;

        // Parse the json response with JsonDataAccess
        JsonDataAccess dataAccess;


        const QVariantMap variant = dataAccess.loadFromBuffer(info).toMap();
        // The qvariant is a map of searches which is extracted as a list
        const QVariantList searchResults = variant["Results"].toList();


        emit resultInterchangesReady(searchResults);

    }else if (info.compare("loginRequest") == 0) {

        emit requestlogin();

    } else {
        emit errorOcurred(info);
    }

    if (request)
        request->deleteLater();

}


LocalityControl::LocalityControl(QObject *parent)
: BaseControl()
, m_active(false)
, m_error(false)
, m_noPermission(false)
, m_localityModel(QVariantMap())
, m_contentModel(new QListDataModel<QObject*>())
, m_householdsModel(new QListDataModel<QObject*>())
, m_interchangesModel(new QListDataModel<QObject*>())
, m_subdivisionsModel(new QListDataModel<QObject*>())
, m_ActivityIndicator(0)
, m_ActivityMoreIndicator(0)
, m_ActivityContentIndicator(0)
{
    //m_contentModel->setGrouping(ItemGrouping::None);
    loadingMore = false;
    m_currentTab = 0;

    m_defaultlocality =  AppSettings::getUserLocalityCode().toInt();
    m_oldDefaultlocality = 0;

    LocalityWorker *worker = new LocalityWorker;
    worker->moveToThread(&workerThread);


}

LocalityControl::~LocalityControl() {
        workerThread.quit();
        workerThread.wait();
}

void LocalityControl::manageSubs()
{
    QString url = AppSettings::getCurrentUserManageSubsLink();
    navigator_invoke(url.toStdString().c_str(), 0);
}

void LocalityControl::reset()
{
    m_error = false;
    m_errorMessage.clear();

    emit localityChanged();
}


void LocalityControl::setHomeSource(AbstractPane *root)
{
    homeSource = root;
}

void LocalityControl::setRoot(Page *root)
{
    rootSource = root;

    qDebug() << "Class: LocalityControl.cpp";

    m_ListView  = rootSource->findChild<ListView*>(QString("locality_listview"));
    m_ListView->resetDataModel();
    m_ListView->setDataModel(m_contentModel);

    //Infinite Scroll
    ListScrollStateHandler::create(m_ListView)
    .onAtEndChanged(this, SLOT(onAtEndChanged(bool)));


    m_ActivityIndicator  = rootSource->findChild<ActivityIndicator*>(QString("actLoadingIndicator"));
    m_ActivityMoreIndicator  = rootSource->findChild<ActivityIndicator*>(QString("moreLoadingIndicator"));
    m_ActivityContentIndicator = rootSource->findChild<ActivityIndicator*>(QString("contenLoadingIndicator"));

}
void LocalityControl::openAction(QString id)
{
    HomeControl::openActionItem(homeSource, id, this);
}
void LocalityControl::onAtEndChanged(bool atEnd)
{
    if (m_currentTab == 0) {
        int page = (m_householdsModel->size() / APIUtil::pageSize);
        float pg = (float)m_householdsModel->size() / (float)APIUtil::pageSize;
        if ((float)pg - (float)page > (float)0)
            page++;

        if (m_householdsModel->size() > 0) {

            if (!loadingMore && atEnd && m_householdsModel->size() >= (APIUtil::pageSize*page)) { //Make sure it just tries to load when there are more items
                loadingMore = true;
                page++;
                requestHouseholds(page);
            }
        }

    }else if (m_currentTab == 1) {
        int page = (m_subdivisionsModel->size() / APIUtil::pageSize);
        float pg = (float)m_subdivisionsModel->size() / (float)APIUtil::pageSize;
        if ((float)pg - (float)page > (float)0)
            page++;

        if (m_subdivisionsModel->size() > 0) {
            if (!loadingMore && atEnd && m_subdivisionsModel->size() >= (APIUtil::pageSize*page)) { //Make sure it just tries to load when there are more items
                loadingMore = true;
                page++;
                requestSubdivisions(page);
            }
        }


    }else if (m_currentTab == 2) {
        int page = (m_interchangesModel->size() / APIUtil::pageSize);
        float pg = (float)m_interchangesModel->size() / (float)APIUtil::pageSize;
        if ((float)pg - (float)page > (float)0)
            page++;

        if (m_interchangesModel->size() > 0) {
            if (!loadingMore && atEnd && m_interchangesModel->size() >= (APIUtil::pageSize*page)) { //Make sure it just tries to load when there are more items
                loadingMore = true;
                page++;
                requestInterchanges(page);
            }
        }

    }


}

void LocalityControl::setAsDefaultLocality() {
    if (!m_localityId.isEmpty()) {

        m_oldDefaultlocality = m_defaultlocality;
        m_defaultlocality = m_localityId.toInt();
        emit defaultLocalityChanged();

        requestSetDefaultLocality(m_localityId);
    }
}

void LocalityControl::setOldAsDefaultLocality() {
    if (m_oldDefaultlocality > 0) {

        m_defaultlocality = m_oldDefaultlocality;
        m_oldDefaultlocality = 0;
        emit oldDefaultLocalityChanged();


        emit defaultLocalityChanged();

        requestSetDefaultLocality(QString::number(m_defaultlocality));
    }
}

//-------------------------------------------------------
//-----------------SET DEFAULT LOCALITY REQUEST-------------------------------------
//-------------------------------------------------------


void LocalityControl::requestSetDefaultLocality(QString defaulLocalityId)
{

    APIUserRequest* request = new APIUserRequest(this);
    bool ok = connect(request, SIGNAL(sigSetDefaultLocalityResponse(QString, bool)), this, SLOT(onSetDefaultLocalityResponse(QString, bool)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
    request->setDefaultLocality(defaulLocalityId, AppSettings::getCurrentUserId());

}


void LocalityControl::onSetDefaultLocalityResponse(const QString &info, bool success)
{
    APIUserRequest *request = qobject_cast<APIUserRequest*>(sender());

    qDebug() << info;
    if (success) {


        emit oldDefaultLocalityChanged();
        emit setDefaultLocalityChanged();


    }else if (info.compare("loginRequest") == 0) {
        m_defaultlocality = m_oldDefaultlocality;
        emit defaultLocalityChanged();

        //emit requestlogin();
        QMetaObject::invokeMethod(rootSource, "openLogin");

    }else {
        m_defaultlocality = m_oldDefaultlocality;
        emit defaultLocalityChanged();
    }


    request->deleteLater();
}



//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//-----------------SET DEFAULT LOCALITY REQUEST-------------------------------------
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx




void LocalityControl::handleError(const QString &error) {
    m_errorMessage = error;
    m_error = true;
    emit statusChanged();

    if (m_ActivityIndicator)
        m_ActivityIndicator->stop();
    if (m_ActivityMoreIndicator)
        m_ActivityMoreIndicator->stop();

}

void LocalityControl::handleNoPermission() {
    m_noPermission = true;
    emit noPermissionChanged();

    if (m_ActivityIndicator)
        m_ActivityIndicator->stop();
    if (m_ActivityMoreIndicator)
        m_ActivityMoreIndicator->stop();

}

void LocalityControl::handleLoginRequest() {
    QMetaObject::invokeMethod(homeSource, "openLogin");
}


//-------------------------------------------------------
//-----------------LOCALITY REQUEST-------------------------------------
//-------------------------------------------------------


void LocalityControl::requestLocality(QString localityId)
{
    m_ActivityIndicator  = rootSource->findChild<ActivityIndicator*>(QString("actLoadingIndicator"));
    m_localityId = localityId;
    if (m_active)
        return;

    m_error = false;
    m_errorMessage = "";
    emit statusChanged();


    //Thread
    if (workerThread.isRunning()) {
        workerThread.terminate();
        workerThread.wait();
    }

    //Start Loading indicator
    m_ActivityIndicator->start();


    LocalityWorker *worker = new LocalityWorker;
    worker->moveToThread(&workerThread);

    connect(&workerThread, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(this, SIGNAL(doRequestLocality(QString)), worker, SLOT(requestLocality(QString)));
    connect(worker, SIGNAL(errorOcurred(QString)), this, SLOT(handleError(QString)));
    connect(worker, SIGNAL(requestlogin()), this, SLOT(handleLoginRequest()));
    connect(worker, SIGNAL(noPermission()), this, SLOT(handleNoPermission()));

    connect(worker, SIGNAL(resultLocalityReady(const QVariant)), this, SLOT(handleLocalityResult(const QVariant)));

    workerThread.start();

    emit doRequestLocality(localityId);


    m_active = true;
}


void LocalityControl::handleLocalityResult(const QVariant &result)
{
    if (!result.isNull()) {
        m_localityModel.clear();
        m_localityModel = result.toMap();

        emit localityChanged();

        m_active = false;
        m_ActivityIndicator->stop();


        //first page

        requestHouseholds(1);
    }


}



//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//-----------------LOCALITY REQUEST-------------------------------------
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx



//-------------------------------------------------------
//-----------------HOUSEHOLDS REQUEST-------------------------------------
//-------------------------------------------------------


/*
 *  LocalityControl::requestHouseholds(int page)
 *
 */
void LocalityControl::requestHouseholds(int page)
{

    if (m_active && page > 1)
        return;

    m_error = false;
    m_errorMessage = "";
    emit statusChanged();

    m_currentTab = 0;

    //Clear if it`s first page
    if (page <= 1) {
        m_contentModel->clear();
        m_householdsModel->clear();

        if (m_ActivityContentIndicator && m_ActivityContentIndicator->isRunning()) {
            m_ActivityContentIndicator->stop();
        }
        if (m_ActivityMoreIndicator && m_ActivityMoreIndicator->isRunning()) {
            m_ActivityMoreIndicator->stop();
        }

        emit contentChanged();
    }


    if (m_householdsModel->isEmpty() || page > 1) {


        //Start Loading indicator
        if (page <= 1)
            m_ActivityContentIndicator->start();
        else
            m_ActivityMoreIndicator->start();
        QApplication::processEvents();

        m_active = true;

        //Thread
        if (workerThread.isRunning()) {
            workerThread.terminate();
            workerThread.wait();
        }

        //call thread
        LocalityWorker *worker = new LocalityWorker;
        worker->moveToThread(&workerThread);

        connect(&workerThread, SIGNAL(finished()), worker, SLOT(deleteLater()));
        connect(this, SIGNAL(doRequestHouseholds(int, QString)), worker, SLOT(requestHouseholds(int, QString)));
        connect(worker, SIGNAL(errorOcurred(QString)), this, SLOT(handleError(QString)));
        connect(worker, SIGNAL(requestlogin()), this, SLOT(handleLoginRequest()));

        connect(worker, SIGNAL(resultHouseholdsReady(const QVariantList)), this, SLOT(handleHouseholdsResult(const QVariantList)));

        workerThread.start();

        emit doRequestHouseholds(page, m_localityId);



    }else {
        //show search
        for (int row = 0; row < m_householdsModel->size(); ++row) {
            m_contentModel->append(m_householdsModel->value(row));
        }
        emit contentChanged();
        m_active = false;
    }




}

void LocalityControl::handleHouseholdsResult(const QVariantList &results)
{
    if (m_currentTab != 0)
        return;

    //UPDATE
    foreach (const QVariant &artifact, results) {
        m_householdsModel->append(new ImageItem(artifact.toMap().value("Photo").toMap().value("SignedURL340").toString(), artifact.toMap(), this));
        m_contentModel->append(new ImageItem(artifact.toMap().value("Photo").toMap().value("SignedURL340").toString(), artifact.toMap(), this));
    }



    m_active = false;
    m_ActivityContentIndicator->stop();
    m_ActivityMoreIndicator->stop();

    loadingMore = false;

    emit contentChanged();

}


//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//-----------------HOUSEHOLDS REQUEST-------------------------------------
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx



//-------------------------------------------------------
//-----------------SUBDIVISIONS REQUEST-------------------------------------
//-------------------------------------------------------


/*
 *  LocalityControl::requestSubdivisions()
 *
 */
void LocalityControl::requestSubdivisions(int page)
{

    if (m_active && page > 1)
        return;

    m_error = false;
    m_errorMessage = "";
    emit statusChanged();

    m_currentTab = 1;

    //Clear if it`s first page
    if (page <= 1) {
        m_contentModel->clear();
        m_subdivisionsModel->clear();

        if (m_ActivityContentIndicator && m_ActivityContentIndicator->isRunning()) {
            m_ActivityContentIndicator->stop();
        }
        if (m_ActivityMoreIndicator && m_ActivityMoreIndicator->isRunning()) {
            m_ActivityMoreIndicator->stop();
        }
        emit contentChanged();
    }



    if (m_subdivisionsModel->isEmpty() || page > 1) {

        //Start Loading indicator
         if (page <= 1)
             m_ActivityContentIndicator->start();
         else
             m_ActivityMoreIndicator->start();
         QApplication::processEvents();

         m_active = true;

         //Thread
         if (workerThread.isRunning()) {
             workerThread.terminate();
             workerThread.wait();
         }

         //call thread
         LocalityWorker *worker = new LocalityWorker;
         worker->moveToThread(&workerThread);

         connect(&workerThread, SIGNAL(finished()), worker, SLOT(deleteLater()));
         connect(this, SIGNAL(doRequestSubdivisions(int, QString)), worker, SLOT(requestSubdivisions(int, QString)));
         connect(worker, SIGNAL(errorOcurred(QString)), this, SLOT(handleError(QString)));
         connect(worker, SIGNAL(requestlogin()), this, SLOT(handleLoginRequest()));

         connect(worker, SIGNAL(resultSubdivisionsReady(const QVariantList)), this, SLOT(handleSubdivisionsResult(const QVariantList)));

         workerThread.start();

         emit doRequestSubdivisions(page, m_localityId);



    }else {
        //show search
        for (int row = 0; row < m_subdivisionsModel->size(); ++row) {
            m_contentModel->append(m_subdivisionsModel->value(row));
        }
        emit contentChanged();
        m_active = false;
    }


}

/*
 * LocalityControl::onSubdivisionsResponse(const QString &info, bool success)
 * Called when Subdivisions request finished
 */
void LocalityControl::handleSubdivisionsResult(const QVariantList &results)
{

    if (m_currentTab != 1)
        return;


    //UPDATE
    foreach (const QVariant &artifact, results) {
        m_subdivisionsModel->append(new ImageItem(artifact.toMap().value("HallPhoto").toMap().value("SignedURL340").toString(), artifact.toMap(), this));
        m_contentModel->append(new ImageItem(artifact.toMap().value("HallPhoto").toMap().value("SignedURL340").toString(), artifact.toMap(), this));
    }

    m_active = false;
    m_ActivityContentIndicator->stop();
    m_ActivityMoreIndicator->stop();

    loadingMore = false;

    emit contentChanged();

}


//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//-----------------SUBDIVISIONS REQUEST-------------------------------------
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx





//-------------------------------------------------------
//-----------------INTERCHANGES REQUEST-------------------------------------
//-------------------------------------------------------


/*
 *  LocalityControl::requestInterchanges()
 *
 */
void LocalityControl::requestInterchanges(int page)
{
    if (m_active && page > 1)
        return;

    m_error = false;
    m_errorMessage = "";
    emit statusChanged();

    m_currentTab = 2;

    //Clear if it`s first page
    if (page <= 1) {
        m_contentModel->clear();
        m_interchangesModel->clear();

        if (m_ActivityContentIndicator && m_ActivityContentIndicator->isRunning()) {
            m_ActivityContentIndicator->stop();
        }
        if (m_ActivityMoreIndicator && m_ActivityMoreIndicator->isRunning()) {
            m_ActivityMoreIndicator->stop();
        }
        emit contentChanged();
    }



    if (m_interchangesModel->isEmpty() || page > 1) {

        //Start Loading indicator
         if (page <= 1)
             m_ActivityContentIndicator->start();
         else
             m_ActivityMoreIndicator->start();
         QApplication::processEvents();

         m_active = true;

         //Thread
         if (workerThread.isRunning()) {
             workerThread.terminate();
             workerThread.wait();
         }

         //call thread
         LocalityWorker *worker = new LocalityWorker;
         worker->moveToThread(&workerThread);

         connect(&workerThread, SIGNAL(finished()), worker, SLOT(deleteLater()));
         connect(this, SIGNAL(doRequestInterchanges(int, QString)), worker, SLOT(requestInterchanges(int, QString)));
         connect(worker, SIGNAL(errorOcurred(QString)), this, SLOT(handleError(QString)));
         connect(worker, SIGNAL(requestlogin()), this, SLOT(handleLoginRequest()));

         connect(worker, SIGNAL(resultInterchangesReady(const QVariantList)), this, SLOT(handleInterchangesResult(const QVariantList)));

         workerThread.start();

         emit doRequestInterchanges(page, m_localityId);



    }else {
        //show search
        for (int row = 0; row < m_interchangesModel->size(); ++row) {
            m_contentModel->append(m_interchangesModel->value(row));
        }
        emit contentChanged();

        m_active = false;
    }


}

void LocalityControl::handleInterchangesResult(const QVariantList &results)
{


    if (m_currentTab != 2)
        return;


    //UPDATE
    foreach (const QVariant &artifact, results) {
        m_interchangesModel->append(new ImageItem("", artifact.toMap(), this));
        m_contentModel->append(new ImageItem("", artifact.toMap(), this));
    }



    m_active = false;
    m_ActivityContentIndicator->stop();
    m_ActivityMoreIndicator->stop();

    loadingMore = false;

    emit contentChanged();
}


//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//-----------------INTERCHANGES REQUEST-------------------------------------
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


void LocalityControl::openSubdivision(QString subdivisionId, QString subdivisionName)
{
    HomeControl::openSubdivisionInfo(homeSource, subdivisionId, subdivisionName);
}

void LocalityControl::openHousehold(QString householdId, QString householdName)
{
    HomeControl::openHouseholdInfo(homeSource, householdId, householdName);
}

void LocalityControl::openLocality(QString localityId, QString localityName)
{
    HomeControl::openLocalityInfo(homeSource, localityId, localityName);
}

bool LocalityControl::error() const
{
    return m_error;
}
bool LocalityControl::noPermission() const
{
    return m_noPermission;
}

int LocalityControl::defaultLocality() const {
    return m_defaultlocality;
}

int LocalityControl::oldDefaultLocality() const {
    return m_oldDefaultlocality;
}

QString LocalityControl::errorMessage() const
{
    return m_errorMessage;
}

QString LocalityControl::dateFromTimestamp(const QString &timestamp) {
    QDateTime date;
    date.setMSecsSinceEpoch(timestamp.toLongLong());
    return date.toString();
}

QVariantMap LocalityControl::localityModel() const
{
    return m_localityModel;
}

bb::cascades::DataModel* LocalityControl::contentModel() const
{
    return m_contentModel;
}


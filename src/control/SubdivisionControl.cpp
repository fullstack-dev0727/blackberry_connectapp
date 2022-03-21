/*
 * Copyright UBT Global.
 *
 *  Created on: 03 Mar 2016
 *      Author: Lucas Bento
 */

#include "SubdivisionControl.hpp"
#include "../imgutil/imageitem.hpp"
#include <bb/cascades/ListScrollStateHandler>
#include <bb/platform/MapInvoker>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <bps/navigator.h>

using namespace bb::cascades;
using namespace bb::data;




void SubdivisionWorker::requestSubdivision(QString subdivisionId)
{

    APISubdivisionsRequest* request = new APISubdivisionsRequest(this);
    bool ok = connect(request, SIGNAL(sigSubdivisionResponse(QString, bool)), this, SLOT(onSubdivisionResponse(QString, bool)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
    request->reqSubdivision(subdivisionId);

}

/*
 * SubdivisionControl::onSubdivisionResponse(const QString &info, bool success)
 * Called when subdivision request finished
 */
void SubdivisionWorker::onSubdivisionResponse(const QString &info, bool success)
{
    APISubdivisionsRequest *request = qobject_cast<APISubdivisionsRequest*>(sender());

    if (success) {
        if (info.trimmed().isEmpty())
            return;

        // Parse the json response with JsonDataAccess
        JsonDataAccess dataAccess;
        QVariant m_subdivisionModel = dataAccess.loadFromBuffer(info);

        emit resultSubdivisionReady(m_subdivisionModel);


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
 *  Worker::requestHouseholds()
 *
 */
void SubdivisionWorker::requestHouseholds(int page, QString subdivisionId)
{

    APIHouseholdsRequest* request = new APIHouseholdsRequest(this);
    bool ok = connect(request, SIGNAL(sigHouseholdsResponse(QString, bool)), this, SLOT(onRequestHouseholdsResponse(QString, bool)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
    request->requestHouseholdsBySubdivision(page, subdivisionId);

}

/*
 * SubdivisionControl::onRequestHouseholdsResponse(const QString &info, bool success)
 * Called when households request finished
 */
void SubdivisionWorker::onRequestHouseholdsResponse(const QString &info, bool success)
{
    APIHouseholdsRequest *request = qobject_cast<APIHouseholdsRequest*>(sender());

    if (success) {

        //parse
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

    }

    if (request)
        request->deleteLater();
}














SubdivisionControl::SubdivisionControl(QObject *parent)
: BaseControl()
, m_active(false)
, m_error(false)
, m_noPermission(false)
, m_subdivisionModel(QVariantMap())
, m_contentModel(new QListDataModel<QObject*>())
{
    //m_contentModel->setGrouping(ItemGrouping::None);
    m_contentModel->setParent(this);
    loadingMore = false;

    SubdivisionWorker *worker = new SubdivisionWorker;
    worker->moveToThread(&workerThread);

}

void SubdivisionControl::manageSubs()
{
    QString url = AppSettings::getCurrentUserManageSubsLink();
    navigator_invoke(url.toStdString().c_str(), 0);
}

void SubdivisionControl::reset()
{
    m_error = false;
    m_errorMessage.clear();

    emit subdivisionChanged();
}


void SubdivisionControl::setHomeSource(AbstractPane *root)
{
    homeSource = root;
}

void SubdivisionControl::setRoot(Page *root)
{
    rootSource = root;
    qDebug() << "Class: SubdivisionControl.cpp";

    m_ListView  = rootSource->findChild<ListView*>(QString("subdivision_listview"));

    //Infinite Scroll
    ListScrollStateHandler::create(m_ListView).onAtEndChanged(this, SLOT(onAtEndChanged(bool)));

    m_ListView->resetDataModel();
    m_ListView->setDataModel(contentModel());


}

void SubdivisionControl::openAction(QString id)
{
    HomeControl::openActionItem(homeSource, id, this);
}

void SubdivisionControl::onAtEndChanged(bool atEnd)
{

    if ((m_contentModel->size()-1) > 0) {
        int page = ((m_contentModel->size()-1) / APIUtil::pageSize);
        float pg = ((float)m_contentModel->size()-1) / (float)APIUtil::pageSize;
        if ((float)pg - (float)page > (float)0)
            page++;

        if (!loadingMore && atEnd && (m_contentModel->size()-1) >= (APIUtil::pageSize*page)) { //Make sure it just tries to load when there are more items

            loadingMore = true;
            //simulate pressing the load more button.

            page++;
            requestHouseholds(page);
        }
    }

}



void SubdivisionControl::handleError(const QString &error) {
    m_errorMessage = error;
    m_error = true;
    emit statusChanged();

    if (m_ActivityIndicator)
        m_ActivityIndicator->stop();


}

void SubdivisionControl::handleNoPermission() {
    m_noPermission = true;
    emit noPermissionChanged();

    if (m_ActivityIndicator)
        m_ActivityIndicator->stop();

}

void SubdivisionControl::handleLoginRequest() {

    QMetaObject::invokeMethod(homeSource, "openLogin");
}


//-------------------------------------------------------
//-----------------SUBDIVISION REQUEST-------------------------------------
//-------------------------------------------------------


/*
 *  SubdivisionControl::requestLocality(QString subdivisionId)
 *
 */

void SubdivisionControl::load()
{
    emit loadSubdivision();

}
void SubdivisionControl::requestSubdivision(QString subdivisionId)
{
    m_ActivityIndicator  = rootSource->findChild<ActivityIndicator*>(QString("actLoadingIndicator"));

    m_subdivisionId = subdivisionId;
    if (m_active)
        return;


    //Start Loading indicator
    m_ActivityIndicator->start();

    //Thread
    if (workerThread.isRunning()) {
        workerThread.terminate();
        workerThread.wait();
    }

    //call thread
    SubdivisionWorker *worker = new SubdivisionWorker;
    worker->moveToThread(&workerThread);

    connect(&workerThread, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(this, SIGNAL(doRequestSubdivision(QString)), worker, SLOT(requestSubdivision(QString)));
    connect(worker, SIGNAL(errorOcurred(QString)), this, SLOT(handleError(QString)));
    connect(worker, SIGNAL(requestlogin()), this, SLOT(handleLoginRequest()));
    connect(worker, SIGNAL(noPermission()), this, SLOT(handleNoPermission()));

    connect(worker, SIGNAL(resultSubdivisionReady(const QVariant)), this, SLOT(handleSubdivisionResult(const QVariant)));

    workerThread.start();

    emit doRequestSubdivision(subdivisionId);


    m_active = true;

}

/*
 * SubdivisionControl::onSubdivisionResponse(const QString &info, bool success)
 * Called when subdivision request finished
 */
void SubdivisionControl::handleSubdivisionResult(const QVariant &result)
{
    if (!result.isNull()) {

        // Parse the json response with JsonDataAccess
        m_subdivisionModel = result.toMap();

        for (QVariantMap::const_iterator iter = m_subdivisionModel.begin(); iter != m_subdivisionModel.end(); ++iter) {
            qDebug() << iter.key() << iter.value();
        }

        m_contentModel->clear();
        m_contentModel->append(new ImageItem(m_subdivisionModel.value("HallPhoto").toMap().value("SignedURL340").toString(), m_subdivisionModel, this));


        //qobject_cast<ImageItem*>(m_contentModel->value(0))->load(); //load subd image


        emit subdivisionChanged();
        emit contentChanged();

        requestHouseholds(1); //page 1


    }

    m_active = false;
    m_ActivityIndicator->stop();

}



//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//-----------------SUBDIVISION REQUEST-------------------------------------
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx



//-------------------------------------------------------
//-----------------HOUSEHOLDS REQUEST-------------------------------------
//-------------------------------------------------------


/*
 *  SubdivisionControl::requestHouseholds()
 *
 */
void SubdivisionControl::requestHouseholds(int page)
{
    //Start Loading indicator
    m_ContentIndicator  = rootSource->findChild<ActivityIndicator*>(QString("actLoadingIndicator"));



    m_ContentIndicator->start();


    //Thread
    if (workerThread.isRunning()) {
        workerThread.terminate();
        workerThread.wait();
    }

    //call thread
    SubdivisionWorker *worker = new SubdivisionWorker;
    worker->moveToThread(&workerThread);

    connect(&workerThread, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(this, SIGNAL(doRequestHouseholds(int, QString)), worker, SLOT(requestHouseholds(int, QString)));
    connect(worker, SIGNAL(errorOcurred(QString)), this, SLOT(handleError(QString)));
    connect(worker, SIGNAL(requestlogin()), this, SLOT(handleLoginRequest()));

    connect(worker, SIGNAL(resultHouseholdsReady(const QVariantList)), this, SLOT(handleHouseholdsResult(const QVariantList)));

    workerThread.start();

    emit doRequestHouseholds(page, m_subdivisionId);
}

/*
 * SubdivisionControl::onRequestHouseholdsResponse(const QString &info, bool success)
 * Called when households request finished
 */
void SubdivisionControl::handleHouseholdsResult(const QVariantList &results)
{

    //UPDATE
    foreach (const QVariant &artifact, results) {
        m_contentModel->append(new ImageItem(artifact.toMap().value("Photo").toMap().value("SignedURL340").toString(), artifact.toMap(), this));
    }

    emit contentChanged();

    m_ContentIndicator->stop();

    m_active = false;
    loadingMore = false;
}



//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//-----------------HOUSEHOLDS REQUEST-------------------------------------
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


void SubdivisionControl::openHousehold(QString householdId, QString householdName)
{
    HomeControl::openHouseholdInfo(homeSource, householdId, householdName);
}

void SubdivisionControl::openLocality(QString localityId)
{
    HomeControl::openLocalityInfo(homeSource, localityId, "");
}

bool SubdivisionControl::error() const
{
    return m_error;
}
bool SubdivisionControl::noPermission() const
{
    return m_noPermission;
}

QString SubdivisionControl::errorMessage() const
{
    return m_errorMessage;
}

QString SubdivisionControl::getId()
{
    return id;
}

QString SubdivisionControl::dateFromTimestamp(const QString &timestamp) {
    QDateTime date;
    date.setMSecsSinceEpoch(timestamp.toLongLong());
    return date.toString();
}

QVariantMap SubdivisionControl::subdivisionModel() const
{
    return m_subdivisionModel;
}

bb::cascades::DataModel* SubdivisionControl::contentModel() const
{
    return m_contentModel;
}

QByteArray SubdivisionControl::encodeQString(const QString& toEncode){
    return toEncode.toUtf8();
}


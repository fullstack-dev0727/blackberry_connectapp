/*
 * Copyright UBT Global.
 *
 *  Created on: 01 Feb 2016
 *      Author: Lucas Bento
 */

#include "SearchControl.hpp"
#include "../imgutil/imageitem.hpp"
#include <bb/cascades/ListScrollStateHandler>
#include <bb/cascades/Label>
#include <bb/cascades/TextField>
#include <bps/virtualkeyboard.h>

using namespace bb::cascades;
using namespace bb::data;



//thread
void SearchWorker::doWork(const int &page, const QString &searchTerm,const QString &resultType, const int &currentTab) {

    m_currentTab = currentTab;
    getSearch(page, searchTerm, resultType);
}


void SearchWorker::getSearch(int page, QString searchTerm, QString resultType) {

    APISearchRequest* request = new APISearchRequest(this);
    bool ok = connect(request, SIGNAL(sigSearchResponse(QString, QString, QString, int, bool)),this,SLOT(onSearchResponse(QString, QString, QString, int, bool)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);

    QString countryCode;
    if (AppSettings::getCountryFilterCode() != "ZZ")
        countryCode = AppSettings::getCountryFilterCode();

    request->requestSearch(page, searchTerm, resultType, countryCode, true);


}

/*
 * SearchControl::onSearchResponse(const QString &info, bool success)
 * Called when search is finished
 */
void SearchWorker::onSearchResponse(const QString &response, const QString &resultType,  const QString &searchTerm, int page, bool success)
{
    APISearchRequest *request = qobject_cast<APISearchRequest*>(sender());



    if (resultType.compare("Member") == 0 && m_currentTab != 1) {
        return;
    }
    else if (resultType.compare("Locality,Subdivision") == 0 && m_currentTab != 2){
        return;
    }
    else if (resultType.isEmpty() && m_currentTab != 0) {
        return;
    }




    if (success) {
        QStringList list = response.split("\n");
        for (int i = 0; i < list.length(); i++) {
            qDebug() << list[i];
        }
        if (response.trimmed().isEmpty())
            return;
        // Parse the json response with JsonDataAccess
        JsonDataAccess dataAccess;
        const QVariantMap variant = dataAccess.loadFromBuffer(response).toMap();
        // The qvariant is a map of searches which is extracted as a list
        QVariantList searchResults = variant["Results"].toList();
        const int totalResults = variant["Total"].toInt();




        //update UI
        emit resultReady(searchResults, resultType, page);

    }else if (response.compare("loginRequest") == 0)
        emit requestlogin();
    else
        emit errorOcurred(response);

    request->deleteLater();
}






//Search Control


SearchControl::SearchControl(QObject *parent)
    : BaseControl()
    , m_active(false)
    , m_error(false)
    , m_searchresult(new QListDataModel<QObject*>())
    , m_searchresultAll(new QListDataModel<QObject*>())
    , m_searchresultPeople(new QListDataModel<QObject*>())
    , m_searchresultLocal(new QListDataModel<QObject*>())
{
    //m_searchresult->setGrouping(ItemGrouping::None);
    //m_searchresultPeople->setGrouping(ItemGrouping::None);
    //m_searchresultLocal->setGrouping(ItemGrouping::None);
    //m_searchresultAll->setGrouping(ItemGrouping::None);

    loadingMore = false;
    m_currentTab = 0;
    m_searchTerm = "";
    m_noresults = false;

    SearchWorker *worker = new SearchWorker;
    worker->moveToThread(&workerThread);

    m_isRegional = (AppSettings::getCurrentUserSubscribedCountriesQt() <= 2);
    emit isRegionalChanged();

}


SearchControl::~SearchControl() {
        workerThread.quit();
        workerThread.wait();
}

void SearchControl::reset()
{
    m_error = false;
    m_errorMessage.clear();

    updateFilter(AppSettings::getCountryFilterName());
    emit seResultChanged();
}

void SearchControl::resetSearch()
{
   m_searchresultAll->clear();
   m_searchresultLocal->clear();
   m_searchresultPeople->clear();

   //virtualkeyboard_show();
}

void SearchControl::setHomeSource(AbstractPane *root)
{
    homeSource = root;
}

void SearchControl::setRoot(Page *root)
{
    rootSource = root;
    qDebug() << "Class: SearchControl.cpp";

    m_ListView  = rootSource->findChild<ListView*>(QString("listView"));
    m_ListView->setDataModel(m_searchresult);

    //Infinite Scroll
    ListScrollStateHandler::create(m_ListView)
            .onAtEndChanged(this, SLOT(onAtEndChanged(bool)));


    updateFilter(AppSettings::getCountryFilterName());
    m_ActivityIndicator  = rootSource->findChild<ActivityIndicator*>(QString("contentLoadingIndicator"));
    m_ActivityMoreIndicator  = rootSource->findChild<ActivityIndicator*>(QString("moreLoadingIndicator"));

}

void SearchControl::openAction(QString id)
{
   HomeControl::openActionItem(homeSource, id, this);
}
void SearchControl::onAtEndChanged(bool atEnd)
{
    if (m_currentTab == 0) {
        int page = (m_searchresultAll->size() / APIUtil::pageSize);
        float pg = (float)m_searchresultAll->size() / (float)APIUtil::pageSize;
        if ((float)pg - (float)page > (float)0)
            page++;

        if (m_searchresultAll->size() > 0) {

            if (!loadingMore && atEnd && m_searchresultAll->size() >= (APIUtil::pageSize*page)) { //Make sure it just tries to load when there are more items
               loadingMore = true;
                page++;
                reqSearch(QString::number(page) ,m_searchTerm , "");
            }
        }

    }else if (m_currentTab == 1) {
        int page = (m_searchresultPeople->size() / APIUtil::pageSize);
        float pg = (float)m_searchresultPeople->size() / (float)APIUtil::pageSize;
        if ((float)pg - (float)page > (float)0)
            page++;

        if (m_searchresultPeople->size() > 0) {
            if (!loadingMore && atEnd && m_searchresultPeople->size() >= (APIUtil::pageSize*page)) { //Make sure it just tries to load when there are more items
               loadingMore = true;
                page++;
                reqSearch(QString::number(page),m_searchTerm , "Member");
            }
        }


    }else if (m_currentTab == 2) {
        int page = (m_searchresultLocal->size() / APIUtil::pageSize);
        float pg = (float)m_searchresultLocal->size() / (float)APIUtil::pageSize;
        if ((float)pg - (float)page > (float)0)
            page++;

        if (m_searchresultLocal->size() > 0) {
            if (!loadingMore && atEnd && m_searchresultLocal->size() >= (APIUtil::pageSize*page)) { //Make sure it just tries to load when there are more items
               loadingMore = true;
                page++;
                reqSearch(QString::number(page),m_searchTerm , "Locality,Subdivision");
            }
        }

    }


}


//-------------------------------------------------------
//-----------------SEARCH REQUEST-------------------------------------
//-------------------------------------------------------


/*
 *  SearchControl::requestSearch()
 *
 */
void SearchControl::reqSearch(QString  pageS, QString searchTerm, QString resultType)
{

    searchTerm = searchTerm.toUtf8();

    m_error = false;
    m_errorMessage = "";
    emit statusChanged();

    m_noresults = false;
    emit resultsChanged();

    int page = pageS.toInt();

    qDebug() << "reauestedSearch";
    if (m_active && page > 1)
        return;

    //Clear if it`s first page
    if (page <= 1) {
        m_searchresult->clear();
        if (m_ActivityIndicator && m_ActivityIndicator->isRunning()) {
            m_ActivityIndicator->stop();
        }
        if (m_ActivityMoreIndicator && m_ActivityMoreIndicator->isRunning()) {
            m_ActivityMoreIndicator->stop();
        }
    }
    emit seResultChanged();

    if (resultType.compare("Member") == 0) {
        m_currentTab = 1;

        if (m_searchresultPeople->isEmpty() || page > 1)
            getSearch(page, searchTerm, resultType);
        else {
            //show search
            for (int row = 0; row < m_searchresultPeople->size(); ++row) {
                m_searchresult->append(m_searchresultPeople->value(row));
            }
            emit seResultChanged();
            //for (int row = 0; row < m_searchresult->size(); ++row) {
            //    qobject_cast<ImageItem*>(m_searchresult->value(row))->load();
            //}
            m_active = false;

        }

    }else if (resultType.compare("Locality,Subdivision") == 0) {
        m_currentTab = 2;

        if (m_searchresultLocal->isEmpty() || page > 1)
            getSearch(page, searchTerm, resultType);
        else {
            //show searchS
            for (int row = 0; row < m_searchresultLocal->size(); ++row) {
                m_searchresult->append(m_searchresultLocal->value(row));
            }
            emit seResultChanged();
            //for (int row = 0; row < m_searchresult->size(); ++row) {
            //    qobject_cast<ImageItem*>(m_searchresult->value(row))->load();
            //}
            m_active = false;

        }
    }else {
        m_currentTab = 0;

        if (m_searchresultAll->isEmpty() || page > 1)
            getSearch(page, searchTerm, resultType);
        else {
            for (int row = 0; row < m_searchresultAll->size(); ++row) {
                m_searchresult->append(m_searchresultAll->value(row));
            }
            emit seResultChanged();
            //for (int row = 0; row < m_searchresult->size(); ++row) {
            //    qobject_cast<ImageItem*>(m_searchresult->value(row))->load();
            //}
            m_active = false;

        }

    }


}

void SearchControl::handleResults(const QVariantList &results, const QString &resultType, const int &page) {



    m_active = false;

    bb::cascades::QListDataModel<QObject*>* dataModel;

    if (resultType.compare("Member") == 0) {
        dataModel = m_searchresultPeople;
    }else if (resultType.compare("Locality,Subdivision") == 0) {
        dataModel = m_searchresultLocal;
    } else {
        dataModel = m_searchresultAll;
    }

    if (page <= 1) {
        dataModel->clear();
        m_searchresult->clear();
    }

    //UPDATE
    foreach (const QVariant &artifact, results) {

        if (!artifact.toMap().value("Result").toMap().value("HallPhoto").toMap().value("SignedURL").isNull()) {
            dataModel->append(new ImageItem(artifact.toMap().value("Result").toMap().value("HallPhoto").toMap().value("SignedURL").toString(), artifact.toMap(), this));
            m_searchresult->append(new ImageItem(artifact.toMap().value("Result").toMap().value("HallPhoto").toMap().value("SignedURL").toString(), artifact.toMap(), this));
        }else{
            dataModel->append(new ImageItem(     artifact.toMap().value("Result").toMap().value("HouseholdPhoto").toMap().value("SignedURL340").toString(), artifact.toMap(), this));
            m_searchresult->append(new ImageItem(artifact.toMap().value("Result").toMap().value("HouseholdPhoto").toMap().value("SignedURL340").toString(), artifact.toMap(), this));
        }
    }

    loadingMore = false;

    //update search
    emit seResultChanged();

    if (m_searchresult->size() <= 0)
        m_noresults = true;
    else
        m_noresults = false;

    emit resultsChanged();

    m_ActivityIndicator->stop();
    m_ActivityMoreIndicator->stop();

}

void SearchControl::handleError(const QString &error) {
    m_errorMessage = error;
    m_error = true;
    emit statusChanged();

    if (m_ActivityIndicator)
        m_ActivityIndicator->stop();
    if (m_ActivityMoreIndicator)
        m_ActivityMoreIndicator->stop();

}

void SearchControl::handleLoginRequest() {

    QMetaObject::invokeMethod(homeSource, "openLogin");
}

void SearchControl::getSearch(int page, QString searchTerm, QString resultType) {



    //Start Loading indicator
    if (page <= 1)
        m_ActivityIndicator->start();
    else
        m_ActivityMoreIndicator->start();
    QApplication::processEvents();

    m_searchTerm = searchTerm;
    m_active = true;




    //Thread
    if (workerThread.isRunning()) {
        workerThread.terminate();
        workerThread.wait();
    }


    SearchWorker *worker = new SearchWorker;
    worker->moveToThread(&workerThread);

    connect(&workerThread, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(this, SIGNAL(operate(int, QString, QString, int)), worker, SLOT(doWork(int, QString, QString, int)));
    connect(worker, SIGNAL(errorOcurred(QString)), this, SLOT(handleError(QString)));
    connect(worker, SIGNAL(requestlogin()), this, SLOT(handleLoginRequest()));

    connect(worker, SIGNAL(resultReady(const QVariantList , const QString , const int)), this, SLOT(handleResults(const QVariantList, const QString, const int)));

    workerThread.start();

    emit operate(page, searchTerm, resultType, m_currentTab);

}


//-------------------------------------------------------
//-----------------SEARCH REQUEST-------------------------------------
//-------------------------------------------------------

/*
 * SearchControl::selectCountryFilter()
 *
 * Open the default country selection to use as a filter
 */
void SearchControl::selectCountryFilter()
{
    QmlDocument *qml = QmlDocument::create("asset:///DetailScreens/CountryChooser.qml");

    //Expose Locality control  to qml
    CountryChooserControl *countryChooserControl = new CountryChooserControl();
    countryChooserControl->setHomeSource(homeSource);

    qml->setContextProperty("_control", countryChooserControl);
    qml->setContextProperty("_main", this);


    Page *page = qml->createRootObject<Page>();

    countryChooserControl->setRoot(page);
    countryChooserControl->requestCountries(true);  //Get data

    NavigationPane* m_navigationPane = homeSource->findChild<NavigationPane*>(QString("homeNavigation"));
    m_navigationPane->push(page);
}

void SearchControl::updateFilter(QString name)
{
    Label* m_FilterButton1 = rootSource->findChild<Label*>(QString("btCountryFilter"));
    if (m_FilterButton1) {
        if (!name.isNull() && !name.isEmpty())
            m_FilterButton1->setText(name);
        else
            m_FilterButton1->setText("All countries");
    }

    Label* m_FilterButton2 = homeSource->findChild<Label*>(QString("btCountryFilter"));
    if (m_FilterButton2){
        if (!name.isNull() && !name.isEmpty())
            m_FilterButton2->setText(name);
        else
            m_FilterButton2->setText("All countries");
    }


}



void SearchControl::openLocality(QString localityId, QString localityName)
{
    HomeControl::openLocalityInfo(homeSource, localityId, localityName);
}

void SearchControl::openSubdivision(QString subdivisionId, QString subdivisionName)
{
    HomeControl::openSubdivisionInfo(homeSource, subdivisionId, subdivisionName);
}

void SearchControl::openHousehold(QString householdId, QString householdName)
{
    HomeControl::openHouseholdInfo(homeSource, householdId, householdName);
}


bool SearchControl::error() const
{
    return m_error;
}

bool SearchControl::isRegional() const
{
    return m_isRegional;
}

bool SearchControl::noresults() const {
    return m_noresults;
}

QString SearchControl::errorMessage() const
{
    return m_errorMessage;
}

QString SearchControl::dateFromTimestamp(const QString &timestamp) {
    QDateTime date;
    date.setMSecsSinceEpoch(timestamp.toLongLong());
    return date.toString();
}

bb::cascades::DataModel* SearchControl::searchresult() const
{
    return m_searchresult;
}

void SearchControl::manageSubs()
{
    QString url = AppSettings::getCurrentUserManageSubsLink();
    navigator_invoke(url.toStdString().c_str(), 0);
}








/*
 * Copyright UBT Global.
 *
 *  Created on: 01 Feb 2016
 *      Author: Lucas Bento
 */

#ifndef SEARCHCONTROL_HPP
#define SEARCHCONTROL_HPP


#include "../AppUi.hpp"
#include <bb/cascades/QListDataModel>
#include <bb/cascades/GroupDataModel>
#include <bb/cascades/Button>
#include <QtCore/QObject>
#include <bb/cascades/NavigationPane>
#include <bb/cascades/ListView>

#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/ActivityIndicator>

#include <bb/data/JsonDataAccess>
#include <bb/utility/i18n/RelativeDateFormatter>

#include <unistd.h>

#include "../api/APISearchRequest.hpp"
#include "../custom/PagedDataModel.hpp"
#include "../AppSettings.hpp"
#include "HomeControl.hpp"
#include "../imgutil/imageitem.hpp"
#include <bps/navigator.h>
#include "../custom/BaseControl.h"

using namespace bb::cascades;


class SearchWorker : public QObject
{
    Q_OBJECT
    QThread workerThread;

public Q_SLOTS:
    void doWork(const int &page, const QString &searchTerm,const QString &resultType, const int &currentTab);
    void getSearch(int page, QString searchTerm, QString resultType) ;
    void onSearchResponse(const QString &response, const QString &resultType,  const QString &searchTerm, int page, bool success);

    Q_SIGNALS:
        void resultReady(const QVariantList &, const QString &, const int &);
        void requestlogin();
        void errorOcurred(const QString &);

    public:
        int m_currentTab;
};



class SearchControl : public BaseControl
{
    Q_OBJECT
    QThread workerThread;

    Q_PROPERTY(bool noresults READ noresults NOTIFY resultsChanged)
    Q_PROPERTY(bool error READ error NOTIFY statusChanged)
    Q_PROPERTY(bool isRegional READ isRegional NOTIFY isRegionalChanged)
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY statusChanged)

    Q_PROPERTY(bb::cascades::DataModel* m_searchresult READ searchresult NOTIFY seResultChanged )

public:
    SearchControl(QObject *parent = 0);
    ~SearchControl();

    void setHomeSource(AbstractPane *root = 0);

    void setRoot(Page *root = 0);



public Q_SLOTS:
    void openAction(QString id);
    void reqSearch(QString page, QString searchTerm, QString resultType);

    void openLocality(QString localityId, QString name);
    void openSubdivision(QString subdivisionId, QString name);
    void openHousehold(QString householdId, QString name);

    void selectCountryFilter();
    void updateFilter(QString name);
    void reset();
    void resetSearch();
    Q_INVOKABLE QString dateFromTimestamp(const QString &timestamp);

    bb::cascades::DataModel* searchresult() const;

    void handleResults(const QVariantList &results, const QString &resultType, const int &page);
    void handleError(const QString &error);
    void handleLoginRequest();

    void manageSubs();


Q_SIGNALS:
    void isRegionalChanged();
    void statusChanged();
    void resultsChanged();
    void seResultChanged();

    void operate(const int &, const QString &,const QString &, const int &);

private Q_SLOTS:

    void onAtEndChanged(bool atEnd);


private:
    /*
     * Parses the JSON response
     */
    void getSearch(int page, QString searchTerm, QString resultType);



    bool active() const;
    bool error() const;
    bool isRegional() const;
    bool noresults() const;
    QString errorMessage() const;



private:
    AbstractPane *homeSource;

    Page *rootSource;
    ActivityIndicator* m_ActivityIndicator;
    ActivityIndicator* m_ActivityMoreIndicator;
    bool m_active;
    bool m_error;
    bool m_isRegional;
    bool m_noresults;
    QString m_errorMessage;
    bb::cascades::QListDataModel<QObject*>* m_searchresult;
    bb::cascades::QListDataModel<QObject*>* m_searchresultAll;
    bb::cascades::QListDataModel<QObject*>* m_searchresultPeople;
    bb::cascades::QListDataModel<QObject*>* m_searchresultLocal;
    ListView* m_ListView;

    bool loadingMore;
    int m_currentTab;
    QString m_searchTerm;

    APISearchRequest* request;

};

#endif

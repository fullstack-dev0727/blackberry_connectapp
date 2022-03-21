/*
 * Copyright (c) 2011-2015 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CONNECTSYNCCONTROL_HPP_
#define CONNECTSYNCCONTROL_HPP_


#include <bb/system/InvokeManager>
#include <bb/Application>
#include <bb/cascades/QListDataModel>
#include <bb/cascades/GroupDataModel>
#include <bb/data/JsonDataAccess>
#include <bb/utility/i18n/RelativeDateFormatter>
#include <bb/cascades/Page>
#include <bb/cascades/ProgressIndicator>
#include <bb/cascades/Sheet>
#include "../../../quazip/src/quazipfile.h"

#include "../database/SQLiteUtil.hpp"
#include <QtGui/QApplication>
#include <QObject>
#include <bb/system/SystemDialog>
#include <bb/system/SystemUiResult>

#include "../api/APICountriesRequest.hpp"
#include "../api/APICountryConfigRequest.hpp"
#include "../api/APISyncHouseholdsRequest.hpp"
#include "../api/APILocalitiesRequest.hpp"
#include "../api/APISubdivisionsRequest.hpp"
#include "../api/APIInterchangesRequest.hpp"

#include "../database/CRUDAboutTable.hpp"
#include "../database/CRUDResourceTable.hpp"
#include "../database/CRUDSearchHouseholdTable.hpp"
#include "../database/CRUDSearchLocalityTable.hpp"
#include "../database/CRUDSearchSubdivisionTable.hpp"
#include "../custom/BaseControl.h"
#include "DownloadManager.hpp"


using namespace bb::cascades;
using namespace bb::system;


class SyncWorker : public BaseControl
{
    Q_OBJECT
    QThread workerThread;

public Q_SLOTS:
    void doSync(const bool &replaceDb);
    void start();
    void cancelT();
    void getDatabase(bool replaceDb);
    void showToast(QString message);

    private slots:

        void onRequestHouseholdsActiveSyncResponse(const QString &info, bool success);
        void onRequestHouseholdsSyncResponse(const QString &info, bool success);
        void onRequestLocalitiesSyncResponse(const QString &info, bool success);
        void onRequestSubdivisionsSyncResponse(const QString &info, bool success);
        void onRequestInterchangesSyncResponse(const QString &info, bool success);
        void onRequestCountriesSyncResponse(const QString &info, bool success);

        void requestHouseholdsActive(int page);
        void requestHouseholds(int page);
        void requestLocalities(int page);
        void requestSubdivisions(int page);
        void requestInterchanges(int page);
        void requestCountries(int page);
        void requestPhotos();



    Q_SIGNALS:
        void updateProgress(const int &, const int &);
        void updateLog(const QString &);
        void requestlogin();
        void errorOcurred(const QString &);
        void processDone(const int &);
        void askUser();
        void downloadDatabase();
        void syncPhotos();


    private:
        int m_householdActiveQt;
        int m_householdActivePage;
        int m_householdQt;
        int m_householdPage;
        int m_localityQt;
        int m_localityPage;
        int m_subdivisionQt;
        int m_subdivisionPage;
        int m_interchangeQt;
        int m_interchangePage;
        int m_countryQt;
        int m_countryPage;
        QString newerThan;

    public:
        APISyncHouseholdsRequest* householdRequest;
        APISyncHouseholdsRequest* householdActiveRequest;
        APILocalitiesRequest* localityRequest;
        APISubdivisionsRequest* subdivisionRequest;
        APIInterchangesRequest* interchangeRequest;
        APICountriesRequest* countryRequest;

        int tempTotalRegs;

        CRUDAboutTable* mCRUDAboutTable;
        CRUDSearchHouseholdTable* mCRUDSearchHouseholdTable;
        CRUDResourceTable* mCRUDResourceTable;
        CRUDSearchLocalityTable* mCRUDSearchLocalityTable;
        CRUDSearchSubdivisionTable* mCRUDSearchSubdivisionTable;


};


/*!
 * @brief Application UI object
 *
 * Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class ConnectSyncControl : public QObject
{
    Q_OBJECT
    QThread workerThread;

    Q_PROPERTY(bool creatingDone READ creatingDone NOTIFY creatingDoneChanged)
    Q_PROPERTY(bool householdDone READ householdDone NOTIFY householdDoneChanged)
    Q_PROPERTY(bool localityDone READ localityDone NOTIFY localityDoneChanged)
    Q_PROPERTY(bool subdivisionDone READ subdivisionDone NOTIFY subdivisionDoneChanged)
    Q_PROPERTY(bool interchangeDone READ interchangeDone NOTIFY interchangeDoneChanged)
    Q_PROPERTY(bool countryDone READ countryDone NOTIFY countryDoneChanged)
    Q_PROPERTY(bool photoDone READ photoDone NOTIFY photoDoneChanged)
    Q_PROPERTY(bool photoExtDone READ photoExtDone NOTIFY photoExtDoneChanged)
    Q_PROPERTY(bool allDone READ allDone NOTIFY allDoneChanged)
    Q_PROPERTY(bool database READ database NOTIFY progressChanged)

    Q_PROPERTY(int synctotal READ syncTotal NOTIFY totalChanged)
    Q_PROPERTY(int syncprogress READ syncProgress NOTIFY progressChanged)

public:
    ConnectSyncControl(QObject *parent);
    virtual ~ConnectSyncControl() {}
    void setHomeSource(AbstractPane *root = 0);
    void setRoot(Page *root = 0);
    bool replaceDb;
    void setSheet(Sheet *sheet = 0);
    void showToast(QString message);

    bool extractDatabase();
    bool extractPhotos();
    bool extractFile(QString m_filename, bool images);


public slots:
    void invoke();
    void cancel();
    void close();

    void onDialogFinished(
            bb::system::SystemUiResult::Type type);

Q_SIGNALS:
    void totalChanged();
    void progressChanged();

    void statusChanged();

    bool creatingDoneChanged();
    bool householdDoneChanged();
    bool localityDoneChanged();
    bool subdivisionDoneChanged();
    bool interchangeDoneChanged();
    bool countryDoneChanged();
    bool photoDoneChanged();
    bool photoExtDoneChanged();
    bool allDoneChanged();


    void doRequestSync(const bool &);
    void doCancel();
    void doStart();
    void doGetDatabase(const bool &);
    void loadMainUser();

private Q_SLOTS:
    void handleUpdateProgress(const int &total, const int &pos);
    void handleUpdateLog(const QString &toLog);
    void handleDone(const int &task);

    void handleError(const QString &error);
    void handleLoginRequest();
    void handleAskUser();
    void handleDownloadDatabase();
    void handleSyncPhotos();


    void downloadingDone(bool paged);

    void imageDownloading();

private:
    DownloadManager *mDownloadManager;
    int currentPhotoPage;

    void downloadPagedPhotos(int page);

    bool creatingDone() const;
    bool householdDone() const;
    bool localityDone() const;
    bool subdivisionDone() const;
    bool interchangeDone() const;
    bool countryDone() const;
    bool photoDone() const;
    bool photoExtDone() const;
    bool allDone() const;
    bool database() const;

    void setScreenMode(int mode);

    int syncTotal() const;
    int syncProgress() const;

    AbstractPane *homeSource;
    Page *rootSource;
    Sheet* mSheet;
    ProgressIndicator *mProgressIndicator;

    int mSyncTotal;
    int mSyncProgress;


    bool m_creatingDone;
    bool m_householdDone;
    bool m_localityDone;
    bool m_subdivisionDone;
    bool m_interchangeDone;
    bool m_countryDone;
    bool m_photoDone;
    bool m_photoExtDone;
    bool m_allDone;
    bool m_database;

    Sheet* pMySheet;

    bb::system::SystemDialog* m_dialog;



};

#endif /* CONNECTSYNCCONTROL_HPP_ */

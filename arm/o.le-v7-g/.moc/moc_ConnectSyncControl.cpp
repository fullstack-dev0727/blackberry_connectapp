/****************************************************************************
** Meta object code from reading C++ file 'ConnectSyncControl.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/control/ConnectSyncControl.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ConnectSyncControl.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SyncWorker[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   12,   11,   11, 0x05,
      38,   11,   11,   11, 0x05,
      57,   11,   11,   11, 0x05,
      72,   11,   11,   11, 0x05,
      94,   11,   11,   11, 0x05,
     111,   11,   11,   11, 0x05,
     121,   11,   11,   11, 0x05,
     140,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     163,  153,   11,   11, 0x0a,
     176,   11,   11,   11, 0x0a,
     184,   11,   11,   11, 0x0a,
     194,  153,   11,   11, 0x0a,
     220,  212,   11,   11, 0x0a,
     252,  239,   11,   11, 0x08,
     304,  239,   11,   11, 0x08,
     350,  239,   11,   11, 0x08,
     396,  239,   11,   11, 0x08,
     444,  239,   11,   11, 0x08,
     492,  239,   11,   11, 0x08,
     542,  537,   11,   11, 0x08,
     571,  537,   11,   11, 0x08,
     594,  537,   11,   11, 0x08,
     617,  537,   11,   11, 0x08,
     642,  537,   11,   11, 0x08,
     667,  537,   11,   11, 0x08,
     689,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SyncWorker[] = {
    "SyncWorker\0\0,\0updateProgress(int,int)\0"
    "updateLog(QString)\0requestlogin()\0"
    "errorOcurred(QString)\0processDone(int)\0"
    "askUser()\0downloadDatabase()\0syncPhotos()\0"
    "replaceDb\0doSync(bool)\0start()\0cancelT()\0"
    "getDatabase(bool)\0message\0showToast(QString)\0"
    "info,success\0"
    "onRequestHouseholdsActiveSyncResponse(QString,bool)\0"
    "onRequestHouseholdsSyncResponse(QString,bool)\0"
    "onRequestLocalitiesSyncResponse(QString,bool)\0"
    "onRequestSubdivisionsSyncResponse(QString,bool)\0"
    "onRequestInterchangesSyncResponse(QString,bool)\0"
    "onRequestCountriesSyncResponse(QString,bool)\0"
    "page\0requestHouseholdsActive(int)\0"
    "requestHouseholds(int)\0requestLocalities(int)\0"
    "requestSubdivisions(int)\0"
    "requestInterchanges(int)\0requestCountries(int)\0"
    "requestPhotos()\0"
};

void SyncWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SyncWorker *_t = static_cast<SyncWorker *>(_o);
        switch (_id) {
        case 0: _t->updateProgress((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 1: _t->updateLog((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->requestlogin(); break;
        case 3: _t->errorOcurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->processDone((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 5: _t->askUser(); break;
        case 6: _t->downloadDatabase(); break;
        case 7: _t->syncPhotos(); break;
        case 8: _t->doSync((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 9: _t->start(); break;
        case 10: _t->cancelT(); break;
        case 11: _t->getDatabase((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->showToast((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->onRequestHouseholdsActiveSyncResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 14: _t->onRequestHouseholdsSyncResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 15: _t->onRequestLocalitiesSyncResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 16: _t->onRequestSubdivisionsSyncResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 17: _t->onRequestInterchangesSyncResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 18: _t->onRequestCountriesSyncResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 19: _t->requestHouseholdsActive((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->requestHouseholds((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->requestLocalities((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->requestSubdivisions((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->requestInterchanges((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->requestCountries((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->requestPhotos(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SyncWorker::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SyncWorker::staticMetaObject = {
    { &BaseControl::staticMetaObject, qt_meta_stringdata_SyncWorker,
      qt_meta_data_SyncWorker, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SyncWorker::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SyncWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SyncWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SyncWorker))
        return static_cast<void*>(const_cast< SyncWorker*>(this));
    return BaseControl::qt_metacast(_clname);
}

int SyncWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseControl::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    }
    return _id;
}

// SIGNAL 0
void SyncWorker::updateProgress(const int & _t1, const int & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SyncWorker::updateLog(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SyncWorker::requestlogin()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void SyncWorker::errorOcurred(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SyncWorker::processDone(const int & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SyncWorker::askUser()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void SyncWorker::downloadDatabase()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void SyncWorker::syncPhotos()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}
static const uint qt_meta_data_ConnectSyncControl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      31,   14, // methods
      12,  169, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      17,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,
      35,   19,   19,   19, 0x05,
      53,   19,   19,   19, 0x05,
      74,   19,   69,   19, 0x05,
      96,   19,   69,   19, 0x05,
     119,   19,   69,   19, 0x05,
     141,   19,   69,   19, 0x05,
     166,   19,   69,   19, 0x05,
     191,   19,   69,   19, 0x05,
     212,   19,   69,   19, 0x05,
     231,   19,   69,   19, 0x05,
     253,   19,   69,   19, 0x05,
     270,   19,   19,   19, 0x05,
     290,   19,   19,   19, 0x05,
     301,   19,   19,   19, 0x05,
     311,   19,   19,   19, 0x05,
     331,   19,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
     346,   19,   19,   19, 0x0a,
     355,   19,   19,   19, 0x0a,
     364,   19,   19,   19, 0x0a,
     377,  372,   19,   19, 0x0a,
     438,  428,   19,   19, 0x08,
     474,  468,   19,   19, 0x08,
     504,  499,   19,   19, 0x08,
     526,  520,   19,   19, 0x08,
     547,   19,   19,   19, 0x08,
     568,   19,   19,   19, 0x08,
     584,   19,   19,   19, 0x08,
     609,   19,   19,   19, 0x08,
     634,  628,   19,   19, 0x08,
     656,   19,   19,   19, 0x08,

 // properties: name, type, flags
     675,   69, 0x01495001,
     688,   69, 0x01495001,
     702,   69, 0x01495001,
     715,   69, 0x01495001,
     731,   69, 0x01495001,
     747,   69, 0x01495001,
     759,   69, 0x01495001,
     769,   69, 0x01495001,
     782,   69, 0x01495001,
     790,   69, 0x01495001,
     803,  799, 0x02495001,
     813,  799, 0x02495001,

 // properties: notify_signal_id
       3,
       4,
       5,
       6,
       7,
       8,
       9,
      10,
      11,
       1,
       0,
       1,

       0        // eod
};

static const char qt_meta_stringdata_ConnectSyncControl[] = {
    "ConnectSyncControl\0\0totalChanged()\0"
    "progressChanged()\0statusChanged()\0"
    "bool\0creatingDoneChanged()\0"
    "householdDoneChanged()\0localityDoneChanged()\0"
    "subdivisionDoneChanged()\0"
    "interchangeDoneChanged()\0countryDoneChanged()\0"
    "photoDoneChanged()\0photoExtDoneChanged()\0"
    "allDoneChanged()\0doRequestSync(bool)\0"
    "doCancel()\0doStart()\0doGetDatabase(bool)\0"
    "loadMainUser()\0invoke()\0cancel()\0"
    "close()\0type\0"
    "onDialogFinished(bb::system::SystemUiResult::Type)\0"
    "total,pos\0handleUpdateProgress(int,int)\0"
    "toLog\0handleUpdateLog(QString)\0task\0"
    "handleDone(int)\0error\0handleError(QString)\0"
    "handleLoginRequest()\0handleAskUser()\0"
    "handleDownloadDatabase()\0handleSyncPhotos()\0"
    "paged\0downloadingDone(bool)\0"
    "imageDownloading()\0creatingDone\0"
    "householdDone\0localityDone\0subdivisionDone\0"
    "interchangeDone\0countryDone\0photoDone\0"
    "photoExtDone\0allDone\0database\0int\0"
    "synctotal\0syncprogress\0"
};

void ConnectSyncControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ConnectSyncControl *_t = static_cast<ConnectSyncControl *>(_o);
        switch (_id) {
        case 0: _t->totalChanged(); break;
        case 1: _t->progressChanged(); break;
        case 2: _t->statusChanged(); break;
        case 3: { bool _r = _t->creatingDoneChanged();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = _t->householdDoneChanged();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: { bool _r = _t->localityDoneChanged();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: { bool _r = _t->subdivisionDoneChanged();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: { bool _r = _t->interchangeDoneChanged();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: { bool _r = _t->countryDoneChanged();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: { bool _r = _t->photoDoneChanged();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { bool _r = _t->photoExtDoneChanged();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: { bool _r = _t->allDoneChanged();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 12: _t->doRequestSync((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 13: _t->doCancel(); break;
        case 14: _t->doStart(); break;
        case 15: _t->doGetDatabase((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 16: _t->loadMainUser(); break;
        case 17: _t->invoke(); break;
        case 18: _t->cancel(); break;
        case 19: _t->close(); break;
        case 20: _t->onDialogFinished((*reinterpret_cast< bb::system::SystemUiResult::Type(*)>(_a[1]))); break;
        case 21: _t->handleUpdateProgress((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 22: _t->handleUpdateLog((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 23: _t->handleDone((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 24: _t->handleError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 25: _t->handleLoginRequest(); break;
        case 26: _t->handleAskUser(); break;
        case 27: _t->handleDownloadDatabase(); break;
        case 28: _t->handleSyncPhotos(); break;
        case 29: _t->downloadingDone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 30: _t->imageDownloading(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ConnectSyncControl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ConnectSyncControl::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ConnectSyncControl,
      qt_meta_data_ConnectSyncControl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ConnectSyncControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ConnectSyncControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ConnectSyncControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ConnectSyncControl))
        return static_cast<void*>(const_cast< ConnectSyncControl*>(this));
    return QObject::qt_metacast(_clname);
}

int ConnectSyncControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 31)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 31;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = creatingDone(); break;
        case 1: *reinterpret_cast< bool*>(_v) = householdDone(); break;
        case 2: *reinterpret_cast< bool*>(_v) = localityDone(); break;
        case 3: *reinterpret_cast< bool*>(_v) = subdivisionDone(); break;
        case 4: *reinterpret_cast< bool*>(_v) = interchangeDone(); break;
        case 5: *reinterpret_cast< bool*>(_v) = countryDone(); break;
        case 6: *reinterpret_cast< bool*>(_v) = photoDone(); break;
        case 7: *reinterpret_cast< bool*>(_v) = photoExtDone(); break;
        case 8: *reinterpret_cast< bool*>(_v) = allDone(); break;
        case 9: *reinterpret_cast< bool*>(_v) = database(); break;
        case 10: *reinterpret_cast< int*>(_v) = syncTotal(); break;
        case 11: *reinterpret_cast< int*>(_v) = syncProgress(); break;
        }
        _id -= 12;
    } else if (_c == QMetaObject::WriteProperty) {
        _id -= 12;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 12;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ConnectSyncControl::totalChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ConnectSyncControl::progressChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ConnectSyncControl::statusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
bool ConnectSyncControl::creatingDoneChanged()
{
    bool _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
    return _t0;
}

// SIGNAL 4
bool ConnectSyncControl::householdDoneChanged()
{
    bool _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
    return _t0;
}

// SIGNAL 5
bool ConnectSyncControl::localityDoneChanged()
{
    bool _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
    return _t0;
}

// SIGNAL 6
bool ConnectSyncControl::subdivisionDoneChanged()
{
    bool _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
    return _t0;
}

// SIGNAL 7
bool ConnectSyncControl::interchangeDoneChanged()
{
    bool _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
    return _t0;
}

// SIGNAL 8
bool ConnectSyncControl::countryDoneChanged()
{
    bool _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
    return _t0;
}

// SIGNAL 9
bool ConnectSyncControl::photoDoneChanged()
{
    bool _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
    return _t0;
}

// SIGNAL 10
bool ConnectSyncControl::photoExtDoneChanged()
{
    bool _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
    return _t0;
}

// SIGNAL 11
bool ConnectSyncControl::allDoneChanged()
{
    bool _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
    return _t0;
}

// SIGNAL 12
void ConnectSyncControl::doRequestSync(const bool & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void ConnectSyncControl::doCancel()
{
    QMetaObject::activate(this, &staticMetaObject, 13, 0);
}

// SIGNAL 14
void ConnectSyncControl::doStart()
{
    QMetaObject::activate(this, &staticMetaObject, 14, 0);
}

// SIGNAL 15
void ConnectSyncControl::doGetDatabase(const bool & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void ConnectSyncControl::loadMainUser()
{
    QMetaObject::activate(this, &staticMetaObject, 16, 0);
}
QT_END_MOC_NAMESPACE

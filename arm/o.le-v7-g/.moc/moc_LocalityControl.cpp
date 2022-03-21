/****************************************************************************
** Meta object code from reading C++ file 'LocalityControl.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/control/LocalityControl.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LocalityControl.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LocalityWorker[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,
      46,   15,   15,   15, 0x05,
      82,   15,   15,   15, 0x05,
     120,   15,   15,   15, 0x05,
     158,   15,   15,   15, 0x05,
     173,   15,   15,   15, 0x05,
     195,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
     221,  210,   15,   15, 0x0a,
     264,  246,   15,   15, 0x0a,
     295,  246,   15,   15, 0x0a,
     328,  246,   15,   15, 0x0a,
     374,  361,   15,   15, 0x0a,
     407,  361,   15,   15, 0x0a,
     449,  361,   15,   15, 0x0a,
     493,  361,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LocalityWorker[] = {
    "LocalityWorker\0\0resultLocalityReady(QVariant)\0"
    "resultHouseholdsReady(QVariantList)\0"
    "resultSubdivisionsReady(QVariantList)\0"
    "resultInterchangesReady(QVariantList)\0"
    "requestlogin()\0errorOcurred(QString)\0"
    "noPermission()\0localityId\0"
    "requestLocality(QString)\0page,m_localityId\0"
    "requestHouseholds(int,QString)\0"
    "requestSubdivisions(int,QString)\0"
    "requestInterchanges(int,QString)\0"
    "info,success\0onLocalityResponse(QString,bool)\0"
    "onRequestHouseholdsResponse(QString,bool)\0"
    "onRequestSubdivisionsResponse(QString,bool)\0"
    "onRequestInterchangesResponse(QString,bool)\0"
};

void LocalityWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LocalityWorker *_t = static_cast<LocalityWorker *>(_o);
        switch (_id) {
        case 0: _t->resultLocalityReady((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 1: _t->resultHouseholdsReady((*reinterpret_cast< const QVariantList(*)>(_a[1]))); break;
        case 2: _t->resultSubdivisionsReady((*reinterpret_cast< const QVariantList(*)>(_a[1]))); break;
        case 3: _t->resultInterchangesReady((*reinterpret_cast< const QVariantList(*)>(_a[1]))); break;
        case 4: _t->requestlogin(); break;
        case 5: _t->errorOcurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->noPermission(); break;
        case 7: _t->requestLocality((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->requestHouseholds((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 9: _t->requestSubdivisions((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 10: _t->requestInterchanges((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 11: _t->onLocalityResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 12: _t->onRequestHouseholdsResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 13: _t->onRequestSubdivisionsResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 14: _t->onRequestInterchangesResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LocalityWorker::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LocalityWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_LocalityWorker,
      qt_meta_data_LocalityWorker, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LocalityWorker::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LocalityWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LocalityWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LocalityWorker))
        return static_cast<void*>(const_cast< LocalityWorker*>(this));
    return QObject::qt_metacast(_clname);
}

int LocalityWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void LocalityWorker::resultLocalityReady(const QVariant & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LocalityWorker::resultHouseholdsReady(const QVariantList & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LocalityWorker::resultSubdivisionsReady(const QVariantList & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void LocalityWorker::resultInterchangesReady(const QVariantList & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void LocalityWorker::requestlogin()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void LocalityWorker::errorOcurred(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void LocalityWorker::noPermission()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}
static const uint qt_meta_data_LocalityControl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      34,   14, // methods
       7,  184, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      33,   16,   16,   16, 0x05,
      51,   16,   16,   16, 0x05,
      76,   16,   16,   16, 0x05,
     104,   16,   16,   16, 0x05,
     132,   16,   16,   16, 0x05,
     154,   16,   16,   16, 0x05,
     183,  181,   16,   16, 0x05,
     216,  181,   16,   16, 0x05,
     251,  181,   16,   16, 0x05,
     286,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
     306,  303,   16,   16, 0x0a,
     337,  326,   16,   16, 0x0a,
     391,  372,   16,   16, 0x0a,
     441,  424,   16,   16, 0x0a,
     496,  472,   16,   16, 0x0a,
     526,   16,   16,   16, 0x0a,
     549,   16,   16,   16, 0x0a,
     575,   16,   16,   16, 0x0a,
     601,  591,  583,   16, 0x0a,
     628,   16,   16,   16, 0x0a,
     641,  326,   16,   16, 0x0a,
     671,  666,   16,   16, 0x0a,
     694,  666,   16,   16, 0x0a,
     719,  666,   16,   16, 0x0a,
     757,  744,   16,   16, 0x08,
     806,  800,   16,   16, 0x08,
     834,  827,   16,   16, 0x08,
     873,  865,   16,   16, 0x08,
     910,  865,   16,   16, 0x08,
     949,  865,   16,   16, 0x08,
     994,  988,   16,   16, 0x08,
    1015,   16,   16,   16, 0x08,
    1036,   16,   16,   16, 0x08,

 // properties: name, type, flags
     988, 1057, 0x01495001,
    1062, 1057, 0x01495001,
    1079, 1075, 0x02495001,
    1095, 1075, 0x02495001,
    1114,  583, 0x0a495001,
    1139, 1127, 0x08495001,
    1180, 1155, 0x00495009,

 // properties: notify_signal_id
       0,
       5,
       2,
       3,
       0,
       1,
      10,

       0        // eod
};

static const char qt_meta_stringdata_LocalityControl[] = {
    "LocalityControl\0\0statusChanged()\0"
    "localityChanged()\0defaultLocalityChanged()\0"
    "oldDefaultLocalityChanged()\0"
    "setDefaultLocalityChanged()\0"
    "noPermissionChanged()\0doRequestLocality(QString)\0"
    ",\0doRequestHouseholds(int,QString)\0"
    "doRequestSubdivisions(int,QString)\0"
    "doRequestInterchanges(int,QString)\0"
    "contentChanged()\0id\0openAction(QString)\0"
    "localityId\0requestSetDefaultLocality(QString)\0"
    "subdivisionId,name\0openSubdivision(QString,QString)\0"
    "householdId,name\0openHousehold(QString,QString)\0"
    "localityId,localityName\0"
    "openLocality(QString,QString)\0"
    "setAsDefaultLocality()\0setOldAsDefaultLocality()\0"
    "reset()\0QString\0timestamp\0"
    "dateFromTimestamp(QString)\0manageSubs()\0"
    "requestLocality(QString)\0page\0"
    "requestHouseholds(int)\0requestSubdivisions(int)\0"
    "requestInterchanges(int)\0info,success\0"
    "onSetDefaultLocalityResponse(QString,bool)\0"
    "atEnd\0onAtEndChanged(bool)\0result\0"
    "handleLocalityResult(QVariant)\0results\0"
    "handleHouseholdsResult(QVariantList)\0"
    "handleSubdivisionsResult(QVariantList)\0"
    "handleInterchangesResult(QVariantList)\0"
    "error\0handleError(QString)\0"
    "handleNoPermission()\0handleLoginRequest()\0"
    "bool\0noPermission\0int\0defaultLocality\0"
    "oldDefaultLocality\0errorMessage\0"
    "QVariantMap\0m_localityModel\0"
    "bb::cascades::DataModel*\0m_contentModel\0"
};

void LocalityControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LocalityControl *_t = static_cast<LocalityControl *>(_o);
        switch (_id) {
        case 0: _t->statusChanged(); break;
        case 1: _t->localityChanged(); break;
        case 2: _t->defaultLocalityChanged(); break;
        case 3: _t->oldDefaultLocalityChanged(); break;
        case 4: _t->setDefaultLocalityChanged(); break;
        case 5: _t->noPermissionChanged(); break;
        case 6: _t->doRequestLocality((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->doRequestHouseholds((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 8: _t->doRequestSubdivisions((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 9: _t->doRequestInterchanges((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 10: _t->contentChanged(); break;
        case 11: _t->openAction((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->requestSetDefaultLocality((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->openSubdivision((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 14: _t->openHousehold((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 15: _t->openLocality((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 16: _t->setAsDefaultLocality(); break;
        case 17: _t->setOldAsDefaultLocality(); break;
        case 18: _t->reset(); break;
        case 19: { QString _r = _t->dateFromTimestamp((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 20: _t->manageSubs(); break;
        case 21: _t->requestLocality((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 22: _t->requestHouseholds((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->requestSubdivisions((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->requestInterchanges((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->onSetDefaultLocalityResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 26: _t->onAtEndChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 27: _t->handleLocalityResult((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 28: _t->handleHouseholdsResult((*reinterpret_cast< const QVariantList(*)>(_a[1]))); break;
        case 29: _t->handleSubdivisionsResult((*reinterpret_cast< const QVariantList(*)>(_a[1]))); break;
        case 30: _t->handleInterchangesResult((*reinterpret_cast< const QVariantList(*)>(_a[1]))); break;
        case 31: _t->handleError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 32: _t->handleNoPermission(); break;
        case 33: _t->handleLoginRequest(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LocalityControl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LocalityControl::staticMetaObject = {
    { &BaseControl::staticMetaObject, qt_meta_stringdata_LocalityControl,
      qt_meta_data_LocalityControl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LocalityControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LocalityControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LocalityControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LocalityControl))
        return static_cast<void*>(const_cast< LocalityControl*>(this));
    return BaseControl::qt_metacast(_clname);
}

int LocalityControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseControl::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 34)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 34;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = error(); break;
        case 1: *reinterpret_cast< bool*>(_v) = noPermission(); break;
        case 2: *reinterpret_cast< int*>(_v) = defaultLocality(); break;
        case 3: *reinterpret_cast< int*>(_v) = oldDefaultLocality(); break;
        case 4: *reinterpret_cast< QString*>(_v) = errorMessage(); break;
        case 5: *reinterpret_cast< QVariantMap*>(_v) = localityModel(); break;
        case 6: *reinterpret_cast< bb::cascades::DataModel**>(_v) = contentModel(); break;
        }
        _id -= 7;
    } else if (_c == QMetaObject::WriteProperty) {
        _id -= 7;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 7;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void LocalityControl::statusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void LocalityControl::localityChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void LocalityControl::defaultLocalityChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void LocalityControl::oldDefaultLocalityChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void LocalityControl::setDefaultLocalityChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void LocalityControl::noPermissionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void LocalityControl::doRequestLocality(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void LocalityControl::doRequestHouseholds(const int & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void LocalityControl::doRequestSubdivisions(const int & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void LocalityControl::doRequestInterchanges(const int & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void LocalityControl::contentChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, 0);
}
QT_END_MOC_NAMESPACE

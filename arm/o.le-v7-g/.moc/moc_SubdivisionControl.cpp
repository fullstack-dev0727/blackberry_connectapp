/****************************************************************************
** Meta object code from reading C++ file 'SubdivisionControl.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/control/SubdivisionControl.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SubdivisionControl.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SubdivisionWorker[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,
      52,   18,   18,   18, 0x05,
      88,   18,   18,   18, 0x05,
     103,   18,   18,   18, 0x05,
     125,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
     154,  140,   18,   18, 0x0a,
     201,  182,   18,   18, 0x0a,
     245,  232,   18,   18, 0x0a,
     281,  232,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SubdivisionWorker[] = {
    "SubdivisionWorker\0\0resultSubdivisionReady(QVariant)\0"
    "resultHouseholdsReady(QVariantList)\0"
    "requestlogin()\0errorOcurred(QString)\0"
    "noPermission()\0subdivisionId\0"
    "requestSubdivision(QString)\0"
    "page,subdivisionId\0requestHouseholds(int,QString)\0"
    "info,success\0onSubdivisionResponse(QString,bool)\0"
    "onRequestHouseholdsResponse(QString,bool)\0"
};

void SubdivisionWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SubdivisionWorker *_t = static_cast<SubdivisionWorker *>(_o);
        switch (_id) {
        case 0: _t->resultSubdivisionReady((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 1: _t->resultHouseholdsReady((*reinterpret_cast< const QVariantList(*)>(_a[1]))); break;
        case 2: _t->requestlogin(); break;
        case 3: _t->errorOcurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->noPermission(); break;
        case 5: _t->requestSubdivision((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->requestHouseholds((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->onSubdivisionResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 8: _t->onRequestHouseholdsResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SubdivisionWorker::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SubdivisionWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SubdivisionWorker,
      qt_meta_data_SubdivisionWorker, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SubdivisionWorker::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SubdivisionWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SubdivisionWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SubdivisionWorker))
        return static_cast<void*>(const_cast< SubdivisionWorker*>(this));
    return QObject::qt_metacast(_clname);
}

int SubdivisionWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void SubdivisionWorker::resultSubdivisionReady(const QVariant & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SubdivisionWorker::resultHouseholdsReady(const QVariantList & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SubdivisionWorker::requestlogin()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void SubdivisionWorker::errorOcurred(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SubdivisionWorker::noPermission()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
static const uint qt_meta_data_SubdivisionControl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       5,  129, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,
      36,   19,   19,   19, 0x05,
      57,   19,   19,   19, 0x05,
      74,   19,   19,   19, 0x05,
      92,   19,   19,   19, 0x05,
     114,   19,   19,   19, 0x05,
     146,  144,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
     182,  179,   19,   19, 0x0a,
     216,  202,   19,   19, 0x0a,
     249,  244,   19,   19, 0x0a,
     289,  272,   19,   19, 0x0a,
     331,  320,   19,   19, 0x0a,
     373,  364,  353,   19, 0x0a,
     396,   19,   19,   19, 0x0a,
     417,   19,  409,   19, 0x0a,
     425,   19,   19,   19, 0x0a,
     443,  433,  409,   19, 0x0a,
     476,  470,   19,   19, 0x08,
     504,  497,   19,   19, 0x08,
     546,  538,   19,   19, 0x08,
     589,  583,   19,   19, 0x08,
     610,   19,   19,   19, 0x08,
     631,   19,   19,   19, 0x08,

 // properties: name, type, flags
     583,  652, 0x01495001,
     657,  652, 0x01495001,
     670,  409, 0x0a495001,
     695,  683, 0x08495001,
     739,  714, 0x00495009,

 // properties: notify_signal_id
       0,
       4,
       0,
       1,
       2,

       0        // eod
};

static const char qt_meta_stringdata_SubdivisionControl[] = {
    "SubdivisionControl\0\0statusChanged()\0"
    "subdivisionChanged()\0contentChanged()\0"
    "loadSubdivision()\0noPermissionChanged()\0"
    "doRequestSubdivision(QString)\0,\0"
    "doRequestHouseholds(int,QString)\0id\0"
    "openAction(QString)\0subdivisionId\0"
    "requestSubdivision(QString)\0page\0"
    "requestHouseholds(int)\0householdId,name\0"
    "openHousehold(QString,QString)\0"
    "localityId\0openLocality(QString)\0"
    "QByteArray\0toEncode\0encodeQString(QString)\0"
    "manageSubs()\0QString\0getId()\0reset()\0"
    "timestamp\0dateFromTimestamp(QString)\0"
    "atEnd\0onAtEndChanged(bool)\0result\0"
    "handleSubdivisionResult(QVariant)\0"
    "results\0handleHouseholdsResult(QVariantList)\0"
    "error\0handleError(QString)\0"
    "handleLoginRequest()\0handleNoPermission()\0"
    "bool\0noPermission\0errorMessage\0"
    "QVariantMap\0m_subdivisionModel\0"
    "bb::cascades::DataModel*\0m_contentModel\0"
};

void SubdivisionControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SubdivisionControl *_t = static_cast<SubdivisionControl *>(_o);
        switch (_id) {
        case 0: _t->statusChanged(); break;
        case 1: _t->subdivisionChanged(); break;
        case 2: _t->contentChanged(); break;
        case 3: _t->loadSubdivision(); break;
        case 4: _t->noPermissionChanged(); break;
        case 5: _t->doRequestSubdivision((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->doRequestHouseholds((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 7: _t->openAction((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->requestSubdivision((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->requestHouseholds((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->openHousehold((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 11: _t->openLocality((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: { QByteArray _r = _t->encodeQString((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QByteArray*>(_a[0]) = _r; }  break;
        case 13: _t->manageSubs(); break;
        case 14: { QString _r = _t->getId();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 15: _t->reset(); break;
        case 16: { QString _r = _t->dateFromTimestamp((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 17: _t->onAtEndChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->handleSubdivisionResult((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 19: _t->handleHouseholdsResult((*reinterpret_cast< const QVariantList(*)>(_a[1]))); break;
        case 20: _t->handleError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 21: _t->handleLoginRequest(); break;
        case 22: _t->handleNoPermission(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SubdivisionControl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SubdivisionControl::staticMetaObject = {
    { &BaseControl::staticMetaObject, qt_meta_stringdata_SubdivisionControl,
      qt_meta_data_SubdivisionControl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SubdivisionControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SubdivisionControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SubdivisionControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SubdivisionControl))
        return static_cast<void*>(const_cast< SubdivisionControl*>(this));
    return BaseControl::qt_metacast(_clname);
}

int SubdivisionControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseControl::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = error(); break;
        case 1: *reinterpret_cast< bool*>(_v) = noPermission(); break;
        case 2: *reinterpret_cast< QString*>(_v) = errorMessage(); break;
        case 3: *reinterpret_cast< QVariantMap*>(_v) = subdivisionModel(); break;
        case 4: *reinterpret_cast< bb::cascades::DataModel**>(_v) = contentModel(); break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::WriteProperty) {
        _id -= 5;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void SubdivisionControl::statusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void SubdivisionControl::subdivisionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void SubdivisionControl::contentChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void SubdivisionControl::loadSubdivision()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void SubdivisionControl::noPermissionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void SubdivisionControl::doRequestSubdivision(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void SubdivisionControl::doRequestHouseholds(const int & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE

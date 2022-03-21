/****************************************************************************
** Meta object code from reading C++ file 'HouseholdControl.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/control/HouseholdControl.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HouseholdControl.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_HouseholdControl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       7,  124, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,
      34,   17,   17,   17, 0x05,
      50,   17,   17,   17, 0x05,
      67,   17,   17,   17, 0x05,
      86,   17,   17,   17, 0x05,
     108,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     128,  125,   17,   17, 0x0a,
     160,  148,   17,   17, 0x0a,
     186,   17,   17,   17, 0x0a,
     215,  203,   17,   17, 0x0a,
     244,   17,   17,   17, 0x0a,
     271,  257,   17,   17, 0x0a,
     307,  296,   17,   17, 0x0a,
     343,  329,   17,   17, 0x0a,
     368,   17,   17,   17, 0x0a,
     401,  392,  381,   17, 0x0a,
     424,   17,   17,   17, 0x0a,
     450,  445,   17,   17, 0x0a,
     505,   17,   17,   17, 0x0a,
     531,  521,  513,   17, 0x0a,
     571,  558,   17,   17, 0x08,
     617,   17,  605,   17, 0x08,

 // properties: name, type, flags
     639,  634, 0x01495001,
     647,  634, 0x01495001,
     654,  634, 0x01495001,
     667,  634, 0x01495001,
     673,  513, 0x0a495001,
     686,  605, 0x08495001,
     728,  703, 0x00495009,

 // properties: notify_signal_id
       2,
       0,
       4,
       1,
       1,
       3,
       5,

       0        // eod
};

static const char qt_meta_stringdata_HouseholdControl[] = {
    "HouseholdControl\0\0activeChanged()\0"
    "statusChanged()\0hdImageChanged()\0"
    "householdChanged()\0noPermissionChanged()\0"
    "contentChanged()\0id\0openAction(QString)\0"
    "householdId\0requestHousehold(QString)\0"
    "requestMembers()\0number,name\0"
    "tCallNumber(QString,QString)\0tSendEmail()\0"
    "householderId\0openHouseholder(QString)\0"
    "localityId\0openLocality(QString)\0"
    "subdivisionId\0openSubdivision(QString)\0"
    "manageSubs()\0QByteArray\0toEncode\0"
    "encodeQString(QString)\0openUpgradeAccount()\0"
    "type\0onDialogCallFinished(bb::system::SystemUiResult::Type)\0"
    "reset()\0QString\0timestamp\0"
    "dateFromTimestamp(QString)\0info,success\0"
    "onHouseholdResponse(QString,bool)\0"
    "QVariantMap\0householdModel()\0bool\0"
    "hdImage\0active\0noPermission\0error\0"
    "errorMessage\0m_householdModel\0"
    "bb::cascades::DataModel*\0m_contentModel\0"
};

void HouseholdControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        HouseholdControl *_t = static_cast<HouseholdControl *>(_o);
        switch (_id) {
        case 0: _t->activeChanged(); break;
        case 1: _t->statusChanged(); break;
        case 2: _t->hdImageChanged(); break;
        case 3: _t->householdChanged(); break;
        case 4: _t->noPermissionChanged(); break;
        case 5: _t->contentChanged(); break;
        case 6: _t->openAction((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->requestHousehold((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->requestMembers(); break;
        case 9: _t->tCallNumber((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 10: _t->tSendEmail(); break;
        case 11: _t->openHouseholder((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->openLocality((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->openSubdivision((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->manageSubs(); break;
        case 15: { QByteArray _r = _t->encodeQString((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QByteArray*>(_a[0]) = _r; }  break;
        case 16: _t->openUpgradeAccount(); break;
        case 17: _t->onDialogCallFinished((*reinterpret_cast< bb::system::SystemUiResult::Type(*)>(_a[1]))); break;
        case 18: _t->reset(); break;
        case 19: { QString _r = _t->dateFromTimestamp((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 20: _t->onHouseholdResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 21: { QVariantMap _r = _t->householdModel();
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData HouseholdControl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject HouseholdControl::staticMetaObject = {
    { &BaseControl::staticMetaObject, qt_meta_stringdata_HouseholdControl,
      qt_meta_data_HouseholdControl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &HouseholdControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *HouseholdControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *HouseholdControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HouseholdControl))
        return static_cast<void*>(const_cast< HouseholdControl*>(this));
    return BaseControl::qt_metacast(_clname);
}

int HouseholdControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseControl::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = hdImage(); break;
        case 1: *reinterpret_cast< bool*>(_v) = active(); break;
        case 2: *reinterpret_cast< bool*>(_v) = noPermission(); break;
        case 3: *reinterpret_cast< bool*>(_v) = error(); break;
        case 4: *reinterpret_cast< QString*>(_v) = errorMessage(); break;
        case 5: *reinterpret_cast< QVariantMap*>(_v) = householdModel(); break;
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
void HouseholdControl::activeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void HouseholdControl::statusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void HouseholdControl::hdImageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void HouseholdControl::householdChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void HouseholdControl::noPermissionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void HouseholdControl::contentChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE

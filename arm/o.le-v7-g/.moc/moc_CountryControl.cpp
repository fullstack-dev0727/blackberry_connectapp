/****************************************************************************
** Meta object code from reading C++ file 'CountryControl.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/control/CountryControl.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CountryControl.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CountryControl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       7,   99, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,
      32,   15,   15,   15, 0x05,
      48,   15,   15,   15, 0x05,
      65,   15,   15,   15, 0x05,
      85,   15,   15,   15, 0x05,
     114,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
     139,  136,   15,   15, 0x0a,
     171,  159,   15,   15, 0x0a,
     212,  195,   15,   15, 0x0a,
     259,  243,   15,   15, 0x0a,
     289,   15,   15,   15, 0x0a,
     302,   15,   15,   15, 0x0a,
     310,   15,   15,   15, 0x0a,
     351,  341,  333,   15, 0x0a,
     391,  378,   15,   15, 0x08,
     423,  378,   15,   15, 0x08,
     471,  465,   15,   15, 0x08,

 // properties: name, type, flags
     497,  492, 0x01495001,
     504,  492, 0x01495001,
     517,  492, 0x01495001,
     523,  333, 0x0a495001,
     536,  333, 0x0a495001,
     568,  556, 0x08495001,
     599,  583, 0x00495009,

 // properties: notify_signal_id
       0,
       5,
       1,
       1,
       4,
       2,
       3,

       0        // eod
};

static const char qt_meta_stringdata_CountryControl[] = {
    "CountryControl\0\0activeChanged()\0"
    "statusChanged()\0countryChanged()\0"
    "localitiesChanged()\0currentLocalityNameChanged()\0"
    "noPermissionChanged()\0id\0openAction(QString)\0"
    "countryCode\0requestCountry(QString)\0"
    "countryCode,page\0requestLocalities(QString,int)\0"
    "localityId,name\0openLocality(QString,QString)\0"
    "manageSubs()\0reset()\0browseOtherCountries()\0"
    "QString\0timestamp\0dateFromTimestamp(QString)\0"
    "info,success\0onCountryResponse(QString,bool)\0"
    "onRequestLocalitiesResponse(QString,bool)\0"
    "atEnd\0onAtEndChanged(bool)\0bool\0active\0"
    "noPermission\0error\0errorMessage\0"
    "currentLocalityName\0QVariantMap\0"
    "m_countryModel\0PagedDataModel*\0"
    "m_localitiesModel\0"
};

void CountryControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CountryControl *_t = static_cast<CountryControl *>(_o);
        switch (_id) {
        case 0: _t->activeChanged(); break;
        case 1: _t->statusChanged(); break;
        case 2: _t->countryChanged(); break;
        case 3: _t->localitiesChanged(); break;
        case 4: _t->currentLocalityNameChanged(); break;
        case 5: _t->noPermissionChanged(); break;
        case 6: _t->openAction((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->requestCountry((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->requestLocalities((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->openLocality((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 10: _t->manageSubs(); break;
        case 11: _t->reset(); break;
        case 12: _t->browseOtherCountries(); break;
        case 13: { QString _r = _t->dateFromTimestamp((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 14: _t->onCountryResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 15: _t->onRequestLocalitiesResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 16: _t->onAtEndChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CountryControl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CountryControl::staticMetaObject = {
    { &BaseControl::staticMetaObject, qt_meta_stringdata_CountryControl,
      qt_meta_data_CountryControl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CountryControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CountryControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CountryControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CountryControl))
        return static_cast<void*>(const_cast< CountryControl*>(this));
    return BaseControl::qt_metacast(_clname);
}

int CountryControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseControl::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = active(); break;
        case 1: *reinterpret_cast< bool*>(_v) = noPermission(); break;
        case 2: *reinterpret_cast< bool*>(_v) = error(); break;
        case 3: *reinterpret_cast< QString*>(_v) = errorMessage(); break;
        case 4: *reinterpret_cast< QString*>(_v) = currentLocalityName(); break;
        case 5: *reinterpret_cast< QVariantMap*>(_v) = countryModel(); break;
        case 6: *reinterpret_cast< PagedDataModel**>(_v) = localitiesModel(); break;
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
void CountryControl::activeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void CountryControl::statusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void CountryControl::countryChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void CountryControl::localitiesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void CountryControl::currentLocalityNameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void CountryControl::noPermissionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE

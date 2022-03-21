/****************************************************************************
** Meta object code from reading C++ file 'CountryChooserControl.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/control/CountryChooserControl.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CountryChooserControl.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CountryChooserControl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       5,   89, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x05,
      39,   22,   22,   22, 0x05,
      55,   22,   22,   22, 0x05,
      74,   22,   22,   22, 0x05,
     103,   22,   22,   22, 0x05,
     121,   22,   22,   22, 0x05,

 // slots: signature, parameters, type, tag, flags
     133,   22,   22,   22, 0x0a,
     159,  149,  141,   22, 0x0a,
     196,  186,   22,   22, 0x0a,
     250,  233,   22,   22, 0x0a,
     290,  273,   22,   22, 0x0a,
     333,  325,   22,   22, 0x0a,
     380,  369,  364,   22, 0x0a,
     420,  407,   22,   22, 0x08,
     461,  407,   22,   22, 0x08,

 // properties: name, type, flags
     504,  364, 0x01495001,
     511,  364, 0x01495001,
     517,  141, 0x0a495001,
     530,  141, 0x0a495001,
     575,  550, 0x00495009,

 // properties: notify_signal_id
       0,
       1,
       1,
       3,
       2,

       0        // eod
};

static const char qt_meta_stringdata_CountryChooserControl[] = {
    "CountryChooserControl\0\0activeChanged()\0"
    "statusChanged()\0countriesChanged()\0"
    "currentLocalityNameChanged()\0"
    "completedSignal()\0completed()\0reset()\0"
    "QString\0timestamp\0dateFromTimestamp(QString)\0"
    "code,name\0openLocalityChooser(QString,QString)\0"
    "showAllCountries\0requestCountries(bool)\0"
    "defaulLocalityId\0requestSetDefaultLocality(QString)\0"
    "id,name\0selectCountry(QString,QString)\0"
    "bool\0localityId\0isDefaultLocality(QString)\0"
    "info,success\0onRequestCountriesResponse(QString,bool)\0"
    "onSetDefaultLocalityResponse(QString,bool)\0"
    "active\0error\0errorMessage\0currentLocalityName\0"
    "bb::cascades::DataModel*\0m_countriesModel\0"
};

void CountryChooserControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CountryChooserControl *_t = static_cast<CountryChooserControl *>(_o);
        switch (_id) {
        case 0: _t->activeChanged(); break;
        case 1: _t->statusChanged(); break;
        case 2: _t->countriesChanged(); break;
        case 3: _t->currentLocalityNameChanged(); break;
        case 4: _t->completedSignal(); break;
        case 5: _t->completed(); break;
        case 6: _t->reset(); break;
        case 7: { QString _r = _t->dateFromTimestamp((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 8: _t->openLocalityChooser((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 9: _t->requestCountries((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->requestSetDefaultLocality((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->selectCountry((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 12: { bool _r = _t->isDefaultLocality((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: _t->onRequestCountriesResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 14: _t->onSetDefaultLocalityResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CountryChooserControl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CountryChooserControl::staticMetaObject = {
    { &BaseControl::staticMetaObject, qt_meta_stringdata_CountryChooserControl,
      qt_meta_data_CountryChooserControl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CountryChooserControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CountryChooserControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CountryChooserControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CountryChooserControl))
        return static_cast<void*>(const_cast< CountryChooserControl*>(this));
    return BaseControl::qt_metacast(_clname);
}

int CountryChooserControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseControl::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = active(); break;
        case 1: *reinterpret_cast< bool*>(_v) = error(); break;
        case 2: *reinterpret_cast< QString*>(_v) = errorMessage(); break;
        case 3: *reinterpret_cast< QString*>(_v) = currentLocalityName(); break;
        case 4: *reinterpret_cast< bb::cascades::DataModel**>(_v) = countriesModel(); break;
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
void CountryChooserControl::activeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void CountryChooserControl::statusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void CountryChooserControl::countriesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void CountryChooserControl::currentLocalityNameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void CountryChooserControl::completedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void CountryChooserControl::completed()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE

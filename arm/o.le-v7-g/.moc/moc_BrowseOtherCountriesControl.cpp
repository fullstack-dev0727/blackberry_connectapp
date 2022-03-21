/****************************************************************************
** Meta object code from reading C++ file 'BrowseOtherCountriesControl.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/control/BrowseOtherCountriesControl.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BrowseOtherCountriesControl.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BrowseOtherCountriesControl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       1,   64, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   28,   28,   28, 0x05,
      45,   28,   28,   28, 0x05,
      61,   28,   28,   28, 0x05,
      82,   28,   28,   28, 0x05,

 // slots: signature, parameters, type, tag, flags
     104,  101,   28,   28, 0x0a,
     124,   28,   28,   28, 0x0a,
     153,  143,   28,   28, 0x0a,
     182,   28,   28,   28, 0x0a,
     215,   28,  190,   28, 0x0a,
     245,  232,   28,   28, 0x08,

 // properties: name, type, flags
     279,  190, 0x00495009,

 // properties: notify_signal_id
       3,

       0        // eod
};

static const char qt_meta_stringdata_BrowseOtherCountriesControl[] = {
    "BrowseOtherCountriesControl\0\0"
    "activeChanged()\0statusChanged()\0"
    "currentUserChanged()\0countriesChanged()\0"
    "id\0openAction(QString)\0requestCountries()\0"
    "code,name\0openCountry(QString,QString)\0"
    "reset()\0bb::cascades::DataModel*\0"
    "countriesModel()\0info,success\0"
    "onCountriesResponse(QString,bool)\0"
    "m_countriesModel\0"
};

void BrowseOtherCountriesControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BrowseOtherCountriesControl *_t = static_cast<BrowseOtherCountriesControl *>(_o);
        switch (_id) {
        case 0: _t->activeChanged(); break;
        case 1: _t->statusChanged(); break;
        case 2: _t->currentUserChanged(); break;
        case 3: _t->countriesChanged(); break;
        case 4: _t->openAction((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->requestCountries(); break;
        case 6: _t->openCountry((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->reset(); break;
        case 8: { bb::cascades::DataModel* _r = _t->countriesModel();
            if (_a[0]) *reinterpret_cast< bb::cascades::DataModel**>(_a[0]) = _r; }  break;
        case 9: _t->onCountriesResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BrowseOtherCountriesControl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BrowseOtherCountriesControl::staticMetaObject = {
    { &BaseControl::staticMetaObject, qt_meta_stringdata_BrowseOtherCountriesControl,
      qt_meta_data_BrowseOtherCountriesControl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BrowseOtherCountriesControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BrowseOtherCountriesControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BrowseOtherCountriesControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BrowseOtherCountriesControl))
        return static_cast<void*>(const_cast< BrowseOtherCountriesControl*>(this));
    return BaseControl::qt_metacast(_clname);
}

int BrowseOtherCountriesControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseControl::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bb::cascades::DataModel**>(_v) = countriesModel(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void BrowseOtherCountriesControl::activeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void BrowseOtherCountriesControl::statusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void BrowseOtherCountriesControl::currentUserChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void BrowseOtherCountriesControl::countriesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE

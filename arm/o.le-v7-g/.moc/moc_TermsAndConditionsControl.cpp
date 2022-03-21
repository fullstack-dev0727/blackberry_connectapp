/****************************************************************************
** Meta object code from reading C++ file 'TermsAndConditionsControl.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/control/TermsAndConditionsControl.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TermsAndConditionsControl.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TermsWorker[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TermsWorker[] = {
    "TermsWorker\0\0handleTerms()\0"
};

void TermsWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TermsWorker *_t = static_cast<TermsWorker *>(_o);
        switch (_id) {
        case 0: _t->handleTerms(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData TermsWorker::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TermsWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TermsWorker,
      qt_meta_data_TermsWorker, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TermsWorker::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TermsWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TermsWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TermsWorker))
        return static_cast<void*>(const_cast< TermsWorker*>(this));
    return QObject::qt_metacast(_clname);
}

int TermsWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_TermsAndConditionsControl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       4,   49, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      27,   26,   26,   26, 0x05,
      43,   26,   26,   26, 0x05,
      59,   26,   26,   26, 0x05,

 // slots: signature, parameters, type, tag, flags
      84,   26,   26,   26, 0x0a,
      99,   26,   26,   26, 0x0a,
     125,  115,  107,   26, 0x0a,
     165,  152,   26,   26, 0x08,

 // properties: name, type, flags
     213,  208, 0x01495001,
     220,  208, 0x01495001,
     226,  107, 0x0a495001,
     251,  239, 0x08495001,

 // properties: notify_signal_id
       0,
       1,
       1,
       2,

       0        // eod
};

static const char qt_meta_stringdata_TermsAndConditionsControl[] = {
    "TermsAndConditionsControl\0\0activeChanged()\0"
    "statusChanged()\0tncScreenStatusChanged()\0"
    "requestTerms()\0reset()\0QString\0timestamp\0"
    "dateFromTimestamp(QString)\0info,success\0"
    "onTermsAndConditionsResponse(QString,bool)\0"
    "bool\0active\0error\0errorMessage\0"
    "QVariantMap\0m_termsnConditions\0"
};

void TermsAndConditionsControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TermsAndConditionsControl *_t = static_cast<TermsAndConditionsControl *>(_o);
        switch (_id) {
        case 0: _t->activeChanged(); break;
        case 1: _t->statusChanged(); break;
        case 2: _t->tncScreenStatusChanged(); break;
        case 3: _t->requestTerms(); break;
        case 4: _t->reset(); break;
        case 5: { QString _r = _t->dateFromTimestamp((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 6: _t->onTermsAndConditionsResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TermsAndConditionsControl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TermsAndConditionsControl::staticMetaObject = {
    { &BaseControl::staticMetaObject, qt_meta_stringdata_TermsAndConditionsControl,
      qt_meta_data_TermsAndConditionsControl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TermsAndConditionsControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TermsAndConditionsControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TermsAndConditionsControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TermsAndConditionsControl))
        return static_cast<void*>(const_cast< TermsAndConditionsControl*>(this));
    return BaseControl::qt_metacast(_clname);
}

int TermsAndConditionsControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseControl::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = active(); break;
        case 1: *reinterpret_cast< bool*>(_v) = error(); break;
        case 2: *reinterpret_cast< QString*>(_v) = errorMessage(); break;
        case 3: *reinterpret_cast< QVariantMap*>(_v) = termsnConditions(); break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::WriteProperty) {
        _id -= 4;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void TermsAndConditionsControl::activeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void TermsAndConditionsControl::statusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void TermsAndConditionsControl::tncScreenStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE

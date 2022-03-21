/****************************************************************************
** Meta object code from reading C++ file 'ContactControl.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/control/ContactControl.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ContactControl.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ContactControl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       6,   84, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,
      32,   15,   15,   15, 0x05,
      48,   15,   15,   15, 0x05,
      66,   15,   15,   15, 0x05,
      90,   15,   15,   15, 0x05,
     106,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
     119,   15,   15,   15, 0x0a,
     153,  140,   15,   15, 0x0a,
     207,  187,   15,   15, 0x0a,
     253,  246,   15,   15, 0x0a,
     274,   15,   15,   15, 0x0a,
     300,  290,  282,   15, 0x0a,
     340,  327,   15,   15, 0x08,
     376,  327,   15,   15, 0x08,

 // properties: name, type, flags
     415,  410, 0x01495001,
     422,  410, 0x01495001,
     428,  282, 0x0a495001,
     441,  282, 0x0a495001,
     450,  282, 0x0a495001,
     469,  457, 0x08495001,

 // properties: notify_signal_id
       0,
       1,
       1,
       2,
       2,
       3,

       0        // eod
};

static const char qt_meta_stringdata_ContactControl[] = {
    "ContactControl\0\0activeChanged()\0"
    "statusChanged()\0userInfoChanged()\0"
    "ctScreenStatusChanged()\0ctMessageSent()\0"
    "ctFinished()\0requestContactInfo()\0"
    "subject,body\0sendContactEmail(QString,QString)\0"
    "userId,subject,body\0"
    "sendUserEmail(QString,QString,QString)\0"
    "number\0tCallNumber(QString)\0reset()\0"
    "QString\0timestamp\0dateFromTimestamp(QString)\0"
    "info,success\0onContactInfoResponse(QString,bool)\0"
    "onSentEmailResponse(QString,bool)\0"
    "bool\0active\0error\0errorMessage\0userName\0"
    "userId\0QVariantMap\0m_ContactInfo\0"
};

void ContactControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ContactControl *_t = static_cast<ContactControl *>(_o);
        switch (_id) {
        case 0: _t->activeChanged(); break;
        case 1: _t->statusChanged(); break;
        case 2: _t->userInfoChanged(); break;
        case 3: _t->ctScreenStatusChanged(); break;
        case 4: _t->ctMessageSent(); break;
        case 5: _t->ctFinished(); break;
        case 6: _t->requestContactInfo(); break;
        case 7: _t->sendContactEmail((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 8: _t->sendUserEmail((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 9: _t->tCallNumber((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->reset(); break;
        case 11: { QString _r = _t->dateFromTimestamp((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 12: _t->onContactInfoResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 13: _t->onSentEmailResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ContactControl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ContactControl::staticMetaObject = {
    { &BaseControl::staticMetaObject, qt_meta_stringdata_ContactControl,
      qt_meta_data_ContactControl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ContactControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ContactControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ContactControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ContactControl))
        return static_cast<void*>(const_cast< ContactControl*>(this));
    return BaseControl::qt_metacast(_clname);
}

int ContactControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseControl::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = active(); break;
        case 1: *reinterpret_cast< bool*>(_v) = error(); break;
        case 2: *reinterpret_cast< QString*>(_v) = errorMessage(); break;
        case 3: *reinterpret_cast< QString*>(_v) = userName(); break;
        case 4: *reinterpret_cast< QString*>(_v) = userId(); break;
        case 5: *reinterpret_cast< QVariantMap*>(_v) = contactInfo(); break;
        }
        _id -= 6;
    } else if (_c == QMetaObject::WriteProperty) {
        _id -= 6;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ContactControl::activeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ContactControl::statusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ContactControl::userInfoChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void ContactControl::ctScreenStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void ContactControl::ctMessageSent()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void ContactControl::ctFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE

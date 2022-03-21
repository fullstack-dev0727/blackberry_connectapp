/****************************************************************************
** Meta object code from reading C++ file 'MyDetailsControl.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/control/MyDetailsControl.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyDetailsControl.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyDetailsControl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      31,   14, // methods
      14,  169, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      14,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,
      34,   17,   17,   17, 0x05,
      50,   17,   17,   17, 0x05,
      68,   17,   17,   17, 0x05,
      91,   17,   17,   17, 0x05,
     113,   17,   17,   17, 0x05,
     139,   17,   17,   17, 0x05,
     167,   17,   17,   17, 0x05,
     186,   17,   17,   17, 0x05,
     206,   17,   17,   17, 0x05,
     228,   17,   17,   17, 0x05,
     245,   17,   17,   17, 0x05,
     264,   17,   17,   17, 0x05,
     283,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     304,   17,   17,   17, 0x0a,
     324,   17,   17,   17, 0x0a,
     337,   17,   17,   17, 0x0a,
     364,  356,   17,   17, 0x0a,
     399,  385,   17,   17, 0x0a,
     432,  424,   17,   17, 0x0a,
     465,  452,   17,   17, 0x0a,
     501,  487,   17,   17, 0x0a,
     541,  524,   17,   17, 0x0a,
     586,  567,   17,   17, 0x0a,
     625,  614,   17,   17, 0x0a,
     660,  647,   17,   17, 0x0a,
     695,  684,   17,   17, 0x0a,
     717,   17,   17,   17, 0x0a,
     743,  733,  725,   17, 0x0a,
     783,  770,   17,   17, 0x08,
     817,  770,   17,   17, 0x08,

 // properties: name, type, flags
     487,  859, 0x01495001,
     452,  859, 0x01495001,
     524,  859, 0x01495001,
     567,  859, 0x01495001,
     864,  725, 0x0a495001,
     873,  725, 0x0a495001,
     424,  725, 0x0a495001,
     886,  725, 0x0a495001,
     896,  725, 0x0a495001,
     906,  725, 0x0a495001,
     918,  859, 0x01495001,
     925,  859, 0x01495001,
     931,  725, 0x0a495001,
     953,  944, 0x88495001,

 // properties: notify_signal_id
       3,
       4,
       5,
       6,
       2,
       9,
      10,
      12,
      11,
      13,
       0,
       1,
       1,
       7,

       0        // eod
};

static const char qt_meta_stringdata_MyDetailsControl[] = {
    "MyDetailsControl\0\0activeChanged()\0"
    "statusChanged()\0commentsChanged()\0"
    "familyUpdatesChanged()\0photoUpdatesChanged()\0"
    "displayWorkPhoneChanged()\0"
    "displayMobilePhoneChanged()\0"
    "myDetailsChanged()\0changeRequestSent()\0"
    "emailAddressChanged()\0addressChanged()\0"
    "homePhoneChanged()\0workPhoneChanged()\0"
    "mobilePhoneChanged()\0sendChangeRequest()\0"
    "manageSubs()\0requestHousehold()\0comment\0"
    "setComments(QString)\0email_address\0"
    "setEmailAddress(QString)\0address\0"
    "setAddress(QString)\0photoUpdates\0"
    "setPhotoUpdates(bool)\0familyUpdates\0"
    "setFamilyUpdates(bool)\0displayWorkPhone\0"
    "setDisplayWorkPhone(bool)\0displayMobilePhone\0"
    "setDisplayMobilePhone(bool)\0work_phone\0"
    "setWorkPhone(QString)\0mobile_phone\0"
    "setMobilePhone(QString)\0home_phone\0"
    "setHomePhone(QString)\0reset()\0QString\0"
    "timestamp\0dateFromTimestamp(QString)\0"
    "info,success\0onHouseholdResponse(QString,bool)\0"
    "onSendChangeRequestResponse(QString,bool)\0"
    "bool\0comments\0emailAddress\0workPhone\0"
    "homePhone\0mobilePhone\0active\0error\0"
    "errorMessage\0QObject*\0myDetails\0"
};

void MyDetailsControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MyDetailsControl *_t = static_cast<MyDetailsControl *>(_o);
        switch (_id) {
        case 0: _t->activeChanged(); break;
        case 1: _t->statusChanged(); break;
        case 2: _t->commentsChanged(); break;
        case 3: _t->familyUpdatesChanged(); break;
        case 4: _t->photoUpdatesChanged(); break;
        case 5: _t->displayWorkPhoneChanged(); break;
        case 6: _t->displayMobilePhoneChanged(); break;
        case 7: _t->myDetailsChanged(); break;
        case 8: _t->changeRequestSent(); break;
        case 9: _t->emailAddressChanged(); break;
        case 10: _t->addressChanged(); break;
        case 11: _t->homePhoneChanged(); break;
        case 12: _t->workPhoneChanged(); break;
        case 13: _t->mobilePhoneChanged(); break;
        case 14: _t->sendChangeRequest(); break;
        case 15: _t->manageSubs(); break;
        case 16: _t->requestHousehold(); break;
        case 17: _t->setComments((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: _t->setEmailAddress((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 19: _t->setAddress((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 20: _t->setPhotoUpdates((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: _t->setFamilyUpdates((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: _t->setDisplayWorkPhone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: _t->setDisplayMobilePhone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->setWorkPhone((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 25: _t->setMobilePhone((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 26: _t->setHomePhone((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 27: _t->reset(); break;
        case 28: { QString _r = _t->dateFromTimestamp((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 29: _t->onHouseholdResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 30: _t->onSendChangeRequestResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MyDetailsControl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MyDetailsControl::staticMetaObject = {
    { &BaseControl::staticMetaObject, qt_meta_stringdata_MyDetailsControl,
      qt_meta_data_MyDetailsControl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyDetailsControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyDetailsControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyDetailsControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyDetailsControl))
        return static_cast<void*>(const_cast< MyDetailsControl*>(this));
    return BaseControl::qt_metacast(_clname);
}

int MyDetailsControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseControl::qt_metacall(_c, _id, _a);
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
        case 0: *reinterpret_cast< bool*>(_v) = familyUpdates(); break;
        case 1: *reinterpret_cast< bool*>(_v) = photoUpdates(); break;
        case 2: *reinterpret_cast< bool*>(_v) = displayWorkPhone(); break;
        case 3: *reinterpret_cast< bool*>(_v) = displayMobilePhone(); break;
        case 4: *reinterpret_cast< QString*>(_v) = comments(); break;
        case 5: *reinterpret_cast< QString*>(_v) = emailAddress(); break;
        case 6: *reinterpret_cast< QString*>(_v) = address(); break;
        case 7: *reinterpret_cast< QString*>(_v) = workPhone(); break;
        case 8: *reinterpret_cast< QString*>(_v) = homePhone(); break;
        case 9: *reinterpret_cast< QString*>(_v) = mobilePhone(); break;
        case 10: *reinterpret_cast< bool*>(_v) = active(); break;
        case 11: *reinterpret_cast< bool*>(_v) = error(); break;
        case 12: *reinterpret_cast< QString*>(_v) = errorMessage(); break;
        case 13: *reinterpret_cast< QObject**>(_v) = myDetails(); break;
        }
        _id -= 14;
    } else if (_c == QMetaObject::WriteProperty) {
        _id -= 14;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 14;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void MyDetailsControl::activeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MyDetailsControl::statusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void MyDetailsControl::commentsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void MyDetailsControl::familyUpdatesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void MyDetailsControl::photoUpdatesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void MyDetailsControl::displayWorkPhoneChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void MyDetailsControl::displayMobilePhoneChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void MyDetailsControl::myDetailsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void MyDetailsControl::changeRequestSent()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void MyDetailsControl::emailAddressChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}

// SIGNAL 10
void MyDetailsControl::addressChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, 0);
}

// SIGNAL 11
void MyDetailsControl::homePhoneChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, 0);
}

// SIGNAL 12
void MyDetailsControl::workPhoneChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 12, 0);
}

// SIGNAL 13
void MyDetailsControl::mobilePhoneChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 13, 0);
}
QT_END_MOC_NAMESPACE

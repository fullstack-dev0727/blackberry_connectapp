/****************************************************************************
** Meta object code from reading C++ file 'APIUserRequest.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/api/APIUserRequest.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'APIUserRequest.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_APIUserRequest[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   16,   15,   15, 0x05,
      66,   16,   15,   15, 0x05,
     110,   16,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
     154,   15,   15,   15, 0x08,
     175,   15,   15,   15, 0x08,
     203,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_APIUserRequest[] = {
    "APIUserRequest\0\0info,success\0"
    "sigCurrentUserResponse(QString,bool)\0"
    "sigSetDefaultLocalityResponse(QString,bool)\0"
    "sigSendChangeResquestResponse(QString,bool)\0"
    "onCurrentUserReply()\0onSetDefaultLocalityReply()\0"
    "onSendChangeRequestReply()\0"
};

void APIUserRequest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        APIUserRequest *_t = static_cast<APIUserRequest *>(_o);
        switch (_id) {
        case 0: _t->sigCurrentUserResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->sigSetDefaultLocalityResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->sigSendChangeResquestResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->onCurrentUserReply(); break;
        case 4: _t->onSetDefaultLocalityReply(); break;
        case 5: _t->onSendChangeRequestReply(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData APIUserRequest::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject APIUserRequest::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_APIUserRequest,
      qt_meta_data_APIUserRequest, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &APIUserRequest::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *APIUserRequest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *APIUserRequest::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_APIUserRequest))
        return static_cast<void*>(const_cast< APIUserRequest*>(this));
    return QObject::qt_metacast(_clname);
}

int APIUserRequest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void APIUserRequest::sigCurrentUserResponse(const QString & _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void APIUserRequest::sigSetDefaultLocalityResponse(const QString & _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void APIUserRequest::sigSendChangeResquestResponse(const QString & _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'APISyncHouseholdsRequest.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/api/APISyncHouseholdsRequest.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'APISyncHouseholdsRequest.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_APISyncHouseholdsRequest[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      39,   26,   25,   25, 0x05,
      75,   26,   25,   25, 0x05,

 // slots: signature, parameters, type, tag, flags
     117,   25,   25,   25, 0x08,
     137,   25,   25,   25, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_APISyncHouseholdsRequest[] = {
    "APISyncHouseholdsRequest\0\0info,success\0"
    "sigHouseholdsResponse(QString,bool)\0"
    "sigHouseholdsActiveResponse(QString,bool)\0"
    "onHouseholdsReply()\0onHouseholdsActiveReply()\0"
};

void APISyncHouseholdsRequest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        APISyncHouseholdsRequest *_t = static_cast<APISyncHouseholdsRequest *>(_o);
        switch (_id) {
        case 0: _t->sigHouseholdsResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->sigHouseholdsActiveResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->onHouseholdsReply(); break;
        case 3: _t->onHouseholdsActiveReply(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData APISyncHouseholdsRequest::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject APISyncHouseholdsRequest::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_APISyncHouseholdsRequest,
      qt_meta_data_APISyncHouseholdsRequest, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &APISyncHouseholdsRequest::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *APISyncHouseholdsRequest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *APISyncHouseholdsRequest::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_APISyncHouseholdsRequest))
        return static_cast<void*>(const_cast< APISyncHouseholdsRequest*>(this));
    return QObject::qt_metacast(_clname);
}

int APISyncHouseholdsRequest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void APISyncHouseholdsRequest::sigHouseholdsResponse(const QString & _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void APISyncHouseholdsRequest::sigHouseholdsActiveResponse(const QString & _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE

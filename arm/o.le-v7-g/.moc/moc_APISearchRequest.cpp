/****************************************************************************
** Meta object code from reading C++ file 'APISearchRequest.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/api/APISearchRequest.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'APISearchRequest.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_APISearchRequest[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      58,   18,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     110,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_APISearchRequest[] = {
    "APISearchRequest\0\0"
    "info,resultType,searchTerm,page,success\0"
    "sigSearchResponse(QString,QString,QString,int,bool)\0"
    "onSearchReply()\0"
};

void APISearchRequest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        APISearchRequest *_t = static_cast<APISearchRequest *>(_o);
        switch (_id) {
        case 0: _t->sigSearchResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 1: _t->onSearchReply(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData APISearchRequest::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject APISearchRequest::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_APISearchRequest,
      qt_meta_data_APISearchRequest, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &APISearchRequest::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *APISearchRequest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *APISearchRequest::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_APISearchRequest))
        return static_cast<void*>(const_cast< APISearchRequest*>(this));
    return QObject::qt_metacast(_clname);
}

int APISearchRequest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void APISearchRequest::sigSearchResponse(const QString & _t1, const QString & _t2, const QString & _t3, int _t4, bool _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

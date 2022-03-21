/****************************************************************************
** Meta object code from reading C++ file 'StatusEventHandler.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/custom/StatusEventHandler.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'StatusEventHandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_StatusEventHandler[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      32,   20,   19,   19, 0x05,
      91,   67,   19,   19, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_StatusEventHandler[] = {
    "StatusEventHandler\0\0status,type\0"
    "networkStatusUpdated(bool,QString)\0"
    "language,country,locale\0"
    "localeUpdated(QString,QString,QString)\0"
};

void StatusEventHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        StatusEventHandler *_t = static_cast<StatusEventHandler *>(_o);
        switch (_id) {
        case 0: _t->networkStatusUpdated((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->localeUpdated((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData StatusEventHandler::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject StatusEventHandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_StatusEventHandler,
      qt_meta_data_StatusEventHandler, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &StatusEventHandler::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *StatusEventHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *StatusEventHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StatusEventHandler))
        return static_cast<void*>(const_cast< StatusEventHandler*>(this));
    if (!strcmp(_clname, "bb::AbstractBpsEventHandler"))
        return static_cast< bb::AbstractBpsEventHandler*>(const_cast< StatusEventHandler*>(this));
    return QObject::qt_metacast(_clname);
}

int StatusEventHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void StatusEventHandler::networkStatusUpdated(bool _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void StatusEventHandler::localeUpdated(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE

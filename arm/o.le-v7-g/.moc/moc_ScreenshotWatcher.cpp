/****************************************************************************
** Meta object code from reading C++ file 'ScreenshotWatcher.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/ScreenshotWatcher.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ScreenshotWatcher.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScreenshotWatcher[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x0a,
      34,   18,   18,   18, 0x0a,
      52,   48,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ScreenshotWatcher[] = {
    "ScreenshotWatcher\0\0onFullscreen()\0"
    "onInvisible()\0str\0showModified(QString)\0"
};

void ScreenshotWatcher::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ScreenshotWatcher *_t = static_cast<ScreenshotWatcher *>(_o);
        switch (_id) {
        case 0: _t->onFullscreen(); break;
        case 1: _t->onInvisible(); break;
        case 2: _t->showModified((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ScreenshotWatcher::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ScreenshotWatcher::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ScreenshotWatcher,
      qt_meta_data_ScreenshotWatcher, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ScreenshotWatcher::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ScreenshotWatcher::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ScreenshotWatcher::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScreenshotWatcher))
        return static_cast<void*>(const_cast< ScreenshotWatcher*>(this));
    return QObject::qt_metacast(_clname);
}

int ScreenshotWatcher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

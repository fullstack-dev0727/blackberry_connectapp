/****************************************************************************
** Meta object code from reading C++ file 'ImageDownloader.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/imgutil/ImageDownloader.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImageDownloader.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ImageDownloader[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       3,   54, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      30,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      53,   16,   45,   16, 0x08,
      63,   59,   16,   16, 0x08,
      88,   16,   79,   16, 0x08,
     101,   16,   96,   16, 0x08,
     111,   16,   16,   16, 0x08,
     127,   16,   16,   16, 0x08,

 // properties: name, type, flags
     145,   79, 0xff495001,
      59,   45, 0x0a495103,
     151,   96, 0x01095401,

 // properties: notify_signal_id
       1,
       0,
       0,

       0        // eod
};

static const char qt_meta_stringdata_ImageDownloader[] = {
    "ImageDownloader\0\0urlChanged()\0"
    "imageChanged()\0QString\0url()\0url\0"
    "setUrl(QString)\0QVariant\0image()\0bool\0"
    "isValid()\0startDownload()\0onReplyFinished()\0"
    "image\0isVaid\0"
};

void ImageDownloader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ImageDownloader *_t = static_cast<ImageDownloader *>(_o);
        switch (_id) {
        case 0: _t->urlChanged(); break;
        case 1: _t->imageChanged(); break;
        case 2: { QString _r = _t->url();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 3: _t->setUrl((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: { QVariant _r = _t->image();
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { bool _r = _t->isValid();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: _t->startDownload(); break;
        case 7: _t->onReplyFinished(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ImageDownloader::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ImageDownloader::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ImageDownloader,
      qt_meta_data_ImageDownloader, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ImageDownloader::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ImageDownloader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ImageDownloader::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImageDownloader))
        return static_cast<void*>(const_cast< ImageDownloader*>(this));
    return QObject::qt_metacast(_clname);
}

int ImageDownloader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QVariant*>(_v) = image(); break;
        case 1: *reinterpret_cast< QString*>(_v) = url(); break;
        case 2: *reinterpret_cast< bool*>(_v) = isValid(); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 1: setUrl(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ImageDownloader::urlChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ImageDownloader::imageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'WebImageView.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/imgutil/WebImageView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WebImageView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WebImageView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       3,   54, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      27,   13,   13,   13, 0x05,
      51,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      72,   68,   13,   13, 0x0a,
      92,   68,   13,   13, 0x0a,
     123,   13,   13,   13, 0x08,
     139,  137,   13,   13, 0x08,

 // methods: signature, parameters, type, tag, flags
     172,   13,   13,   13, 0x02,

 // properties: name, type, flags
     197,  185, 0x08495103,
      68,  185, 0x08495103,
     218,  212, 0x87495001,

 // properties: notify_signal_id
       1,
       0,
       2,

       0        // eod
};

static const char qt_meta_stringdata_WebImageView[] = {
    "WebImageView\0\0urlChanged()\0"
    "postLoadingUrlChanged()\0loadingChanged()\0"
    "url\0setUrl(QVariantMap)\0"
    "setPostLoadingUrl(QVariantMap)\0"
    "imageLoaded()\0,\0dowloadProgressed(qint64,qint64)\0"
    "clearCache()\0QVariantMap\0postLoadingUrl\0"
    "float\0loading\0"
};

void WebImageView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WebImageView *_t = static_cast<WebImageView *>(_o);
        switch (_id) {
        case 0: _t->urlChanged(); break;
        case 1: _t->postLoadingUrlChanged(); break;
        case 2: _t->loadingChanged(); break;
        case 3: _t->setUrl((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 4: _t->setPostLoadingUrl((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 5: _t->imageLoaded(); break;
        case 6: _t->dowloadProgressed((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 7: _t->clearCache(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WebImageView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WebImageView::staticMetaObject = {
    { &bb::cascades::ImageView::staticMetaObject, qt_meta_stringdata_WebImageView,
      qt_meta_data_WebImageView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WebImageView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WebImageView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WebImageView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WebImageView))
        return static_cast<void*>(const_cast< WebImageView*>(this));
    typedef bb::cascades::ImageView QMocSuperClass;
    return QMocSuperClass::qt_metacast(_clname);
}

int WebImageView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    typedef bb::cascades::ImageView QMocSuperClass;
    _id = QMocSuperClass::qt_metacall(_c, _id, _a);
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
        case 0: *reinterpret_cast< QVariantMap*>(_v) = postLoadingUrl(); break;
        case 1: *reinterpret_cast< QVariantMap*>(_v) = url(); break;
        case 2: *reinterpret_cast< float*>(_v) = loading(); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setPostLoadingUrl(*reinterpret_cast< QVariantMap*>(_v)); break;
        case 1: setUrl(*reinterpret_cast< QVariantMap*>(_v)); break;
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
void WebImageView::urlChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void WebImageView::postLoadingUrlChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void WebImageView::loadingChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE

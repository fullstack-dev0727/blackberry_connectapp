/****************************************************************************
** Meta object code from reading C++ file 'PagedDataModel.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/custom/PagedDataModel.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PagedDataModel.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PagedDataModel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       1,   24, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,

 // methods: signature, parameters, type, tag, flags
      45,   35,   15,   15, 0x02,

 // properties: name, type, flags
      74,   70, 0x02495001,

 // properties: notify_signal_id
       0,

       0        // eod
};

static const char qt_meta_stringdata_PagedDataModel[] = {
    "PagedDataModel\0\0itemCountChanged()\0"
    "indexPath\0addItemsAt(QVariantList)\0"
    "int\0itemCount\0"
};

void PagedDataModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PagedDataModel *_t = static_cast<PagedDataModel *>(_o);
        switch (_id) {
        case 0: _t->itemCountChanged(); break;
        case 1: _t->addItemsAt((*reinterpret_cast< const QVariantList(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PagedDataModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PagedDataModel::staticMetaObject = {
    { &bb::cascades::QVariantListDataModel::staticMetaObject, qt_meta_stringdata_PagedDataModel,
      qt_meta_data_PagedDataModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PagedDataModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PagedDataModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PagedDataModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PagedDataModel))
        return static_cast<void*>(const_cast< PagedDataModel*>(this));
    typedef bb::cascades::QVariantListDataModel QMocSuperClass;
    return QMocSuperClass::qt_metacast(_clname);
}

int PagedDataModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    typedef bb::cascades::QVariantListDataModel QMocSuperClass;
    _id = QMocSuperClass::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = itemCount(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void PagedDataModel::itemCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'SearchControl.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/control/SearchControl.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SearchControl.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SearchWorker[] = {

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
      17,   14,   13,   13, 0x05,
      55,   13,   13,   13, 0x05,
      70,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
     130,   92,   13,   13, 0x0a,
     189,  162,   13,   13, 0x0a,
     264,  220,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SearchWorker[] = {
    "SearchWorker\0\0,,\0resultReady(QVariantList,QString,int)\0"
    "requestlogin()\0errorOcurred(QString)\0"
    "page,searchTerm,resultType,currentTab\0"
    "doWork(int,QString,QString,int)\0"
    "page,searchTerm,resultType\0"
    "getSearch(int,QString,QString)\0"
    "response,resultType,searchTerm,page,success\0"
    "onSearchResponse(QString,QString,QString,int,bool)\0"
};

void SearchWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SearchWorker *_t = static_cast<SearchWorker *>(_o);
        switch (_id) {
        case 0: _t->resultReady((*reinterpret_cast< const QVariantList(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3]))); break;
        case 1: _t->requestlogin(); break;
        case 2: _t->errorOcurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->doWork((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4]))); break;
        case 4: _t->getSearch((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 5: _t->onSearchResponse((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SearchWorker::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SearchWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SearchWorker,
      qt_meta_data_SearchWorker, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SearchWorker::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SearchWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SearchWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SearchWorker))
        return static_cast<void*>(const_cast< SearchWorker*>(this));
    return QObject::qt_metacast(_clname);
}

int SearchWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void SearchWorker::resultReady(const QVariantList & _t1, const QString & _t2, const int & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SearchWorker::requestlogin()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void SearchWorker::errorOcurred(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
static const uint qt_meta_data_SearchControl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       5,  119, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      35,   14,   14,   14, 0x05,
      51,   14,   14,   14, 0x05,
      68,   14,   14,   14, 0x05,
      90,   86,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     126,  123,   14,   14, 0x0a,
     173,  146,   14,   14, 0x0a,
     224,  208,   14,   14, 0x0a,
     273,  254,   14,   14, 0x0a,
     323,  306,   14,   14, 0x0a,
     354,   14,   14,   14, 0x0a,
     381,  376,   14,   14, 0x0a,
     403,   14,   14,   14, 0x0a,
     411,   14,   14,   14, 0x0a,
     443,  433,  425,   14, 0x0a,
     495,   14,  470,   14, 0x0a,
     534,  510,   14,   14, 0x0a,
     580,  574,   14,   14, 0x0a,
     601,   14,   14,   14, 0x0a,
     622,   14,   14,   14, 0x0a,
     641,  635,   14,   14, 0x08,

 // properties: name, type, flags
     667,  662, 0x01495001,
     574,  662, 0x01495001,
     677,  662, 0x01495001,
     688,  425, 0x0a495001,
     701,  470, 0x00495009,

 // properties: notify_signal_id
       2,
       1,
       0,
       1,
       3,

       0        // eod
};

static const char qt_meta_stringdata_SearchControl[] = {
    "SearchControl\0\0isRegionalChanged()\0"
    "statusChanged()\0resultsChanged()\0"
    "seResultChanged()\0,,,\0"
    "operate(int,QString,QString,int)\0id\0"
    "openAction(QString)\0page,searchTerm,resultType\0"
    "reqSearch(QString,QString,QString)\0"
    "localityId,name\0openLocality(QString,QString)\0"
    "subdivisionId,name\0openSubdivision(QString,QString)\0"
    "householdId,name\0openHousehold(QString,QString)\0"
    "selectCountryFilter()\0name\0"
    "updateFilter(QString)\0reset()\0"
    "resetSearch()\0QString\0timestamp\0"
    "dateFromTimestamp(QString)\0"
    "bb::cascades::DataModel*\0searchresult()\0"
    "results,resultType,page\0"
    "handleResults(QVariantList,QString,int)\0"
    "error\0handleError(QString)\0"
    "handleLoginRequest()\0manageSubs()\0"
    "atEnd\0onAtEndChanged(bool)\0bool\0"
    "noresults\0isRegional\0errorMessage\0"
    "m_searchresult\0"
};

void SearchControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SearchControl *_t = static_cast<SearchControl *>(_o);
        switch (_id) {
        case 0: _t->isRegionalChanged(); break;
        case 1: _t->statusChanged(); break;
        case 2: _t->resultsChanged(); break;
        case 3: _t->seResultChanged(); break;
        case 4: _t->operate((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4]))); break;
        case 5: _t->openAction((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->reqSearch((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 7: _t->openLocality((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->openSubdivision((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 9: _t->openHousehold((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 10: _t->selectCountryFilter(); break;
        case 11: _t->updateFilter((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->reset(); break;
        case 13: _t->resetSearch(); break;
        case 14: { QString _r = _t->dateFromTimestamp((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 15: { bb::cascades::DataModel* _r = _t->searchresult();
            if (_a[0]) *reinterpret_cast< bb::cascades::DataModel**>(_a[0]) = _r; }  break;
        case 16: _t->handleResults((*reinterpret_cast< const QVariantList(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3]))); break;
        case 17: _t->handleError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 18: _t->handleLoginRequest(); break;
        case 19: _t->manageSubs(); break;
        case 20: _t->onAtEndChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SearchControl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SearchControl::staticMetaObject = {
    { &BaseControl::staticMetaObject, qt_meta_stringdata_SearchControl,
      qt_meta_data_SearchControl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SearchControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SearchControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SearchControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SearchControl))
        return static_cast<void*>(const_cast< SearchControl*>(this));
    return BaseControl::qt_metacast(_clname);
}

int SearchControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseControl::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = noresults(); break;
        case 1: *reinterpret_cast< bool*>(_v) = error(); break;
        case 2: *reinterpret_cast< bool*>(_v) = isRegional(); break;
        case 3: *reinterpret_cast< QString*>(_v) = errorMessage(); break;
        case 4: *reinterpret_cast< bb::cascades::DataModel**>(_v) = searchresult(); break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::WriteProperty) {
        _id -= 5;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void SearchControl::isRegionalChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void SearchControl::statusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void SearchControl::resultsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void SearchControl::seResultChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void SearchControl::operate(const int & _t1, const QString & _t2, const QString & _t3, const int & _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE

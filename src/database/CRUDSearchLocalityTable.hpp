
#ifndef CRUDSEARCHLOCALITYTABLE_HPP_
#define CRUDSEARCHLOCALITYTABLE_HPP_


#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/OrientationSupport>
#include <bb/system/SystemDialog>
#include "SQLiteUtil.hpp"
#include "CRUDBase.hpp"

#include <QtSql/QtSql>

using namespace bb::cascades;
using namespace bb::system;


class CRUDSearchLocalityTable: public CRUDBase
{
public:
    CRUDSearchLocalityTable();
    virtual ~CRUDSearchLocalityTable();

    bool insertOrUpdate(
                            QString localityTableID,
                            QString localityID,
                            QString name,
                            QString countryCode
    );
    bool insertOrUpdateBatch(
                            QList<QString> localityTableIDs,
                            QList<QString> localityIDs,
                            QList<QString> names,
                            QList<QString> countryCodes
    );
    bool deleteAll();
    bool deleteResource(QString resourceId);

};




#endif /* CRUDSEARCHLOCALITYTABLE_HPP_ */

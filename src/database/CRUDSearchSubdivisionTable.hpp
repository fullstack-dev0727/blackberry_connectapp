
#ifndef CRUDSEARCHSUBDIVISIONTABLE_HPP_
#define CRUDSEARCHSUBDIVISIONTABLE_HPP_


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


class CRUDSearchSubdivisionTable: public CRUDBase
{
public:
    CRUDSearchSubdivisionTable();
    virtual ~CRUDSearchSubdivisionTable();

    bool insertOrUpdate(
                            QString subdivisionTableID,
                            QString subdivisionID,
                            QString name,
                            QString countryCode
    );
    bool insertOrUpdateBatch(
                            QList<QString> subdivisionTableIDs,
                            QList<QString> subdivisionIDs,
                            QList<QString> names,
                            QList<QString> countryCodes
    );
    bool deleteAll();
    bool deleteResource(QString resourceId);

};




#endif /* CRUDSEARCHSUBDIVISIONTABLE_HPP_ */

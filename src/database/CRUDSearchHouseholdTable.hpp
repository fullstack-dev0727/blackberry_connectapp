#ifndef CRUDSEARCHHOUSEHOLDTABLE_HPP_
#define CRUDSEARCHHOUSEHOLDTABLE_HPP_


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


class CRUDSearchHouseholdTable: public CRUDBase
{
public:
    CRUDSearchHouseholdTable();
    virtual ~CRUDSearchHouseholdTable();

    bool insertOrUpdate(
                            QString householdTableID,
                            QString householdID,
                            QString firstName,
                            QString firstNameReversed,
                            QString lastName,
                            QString lastNameReversed,
                            QString lastNameFirstName,
                            QString fullName,
                            QString fullNameReversed,
                            QString countryCode
    );

    bool insertOrUpdateBatch(
                            QList<QString> householdTableID,
                            QList<QString> householdID,
                            QList<QString> firstName,
                            QList<QString> firstNameReversed,
                            QList<QString> lastName,
                            QList<QString> lastNameReversed,
                            QList<QString> lastNameFirstName,
                            QList<QString> fullName,
                            QList<QString> fullNameReversed,
                            QList<QString> countryCode
    );

    bool deleteAll();
    bool deleteResource(QString resourceId);

};




#endif /* CRUDSEARCHHOUSEHOLDTABLE_HPP_ */

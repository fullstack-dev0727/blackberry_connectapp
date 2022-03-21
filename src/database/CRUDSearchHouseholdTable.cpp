

#include "CRUDSearchHouseholdTable.hpp"
#include <bb/data/JsonDataAccess>
#include "../api/APIUtil.hpp"
#define INTERVAL 80
using namespace bb::data;

CRUDSearchHouseholdTable::CRUDSearchHouseholdTable()
{
}

CRUDSearchHouseholdTable::~CRUDSearchHouseholdTable()
{
}
bool CRUDSearchHouseholdTable::insertOrUpdate(
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
)
{


    QSqlDatabase database = SQLConnection();

    if (!database.tables().contains("search_household")) {
        qDebug() << "Create record error: search_household table does not exist.";
        return false;
    } else {
        QSqlQuery query(database);
        query.prepare("INSERT INTO search_household (resource_table_id,resource_id, first_name, first_name_reversed, last_name, last_name_reversed,"
                " full_name, full_name_reversed, last_name_first_name, country_code) "
                "VALUES(:resource_table_id, :resource_id, :first_name, :first_name_reversed, :last_name, "
                ":last_name_reversed, :full_name, :full_name_reversed, :last_name_first_name, :country_code)" );

        query.bindValue(":resource_table_id", householdTableID.toInt() );
        query.bindValue(":resource_id", householdID.toInt() );
        query.bindValue(":first_name", firstName);
        query.bindValue(":first_name_reversed", firstNameReversed);
        query.bindValue(":last_name", lastName);
        query.bindValue(":last_name_reversed", lastNameReversed);
        query.bindValue(":full_name", fullName);
        query.bindValue(":full_name_reversed", fullNameReversed);
        query.bindValue(":last_name_first_name", lastNameFirstName);
        query.bindValue(":country_code", countryCode);

        // Note that no SQL Statement is passed to 'exec' as it is a prepared statement.
        if (query.exec()) {
            database.close();

            return true;

        } else {
            const QSqlError error = query.lastError();
            qDebug() << "Insert Search Household error: " + error.text();

            query.finish();
            database.close();

            return false;

        }

        query.finish();
    }
}
bool CRUDSearchHouseholdTable::insertOrUpdateBatch(
                        QList<QString> householdTableIDs,
                        QList<QString> householdIDs,
                        QList<QString> firstNames,
                        QList<QString> firstNameReverseds,
                        QList<QString> lastNames,
                        QList<QString> lastNameReverseds,
                        QList<QString> lastNameFirstNames,
                        QList<QString> fullNames,
                        QList<QString> fullNameReverseds,
                        QList<QString> countryCodes
)
{


    QSqlDatabase database = SQLConnection();

    if (!database.tables().contains("search_household")) {
        qDebug() << "Create record error: search_household table does not exist.";
        return false;
    } else {
        int totalSize = householdTableIDs.size();
        int currentIndex = 0;
        while (currentIndex < totalSize) {
            QSqlQuery sqlQuery(database);
            QString query = "INSERT INTO search_household (resource_table_id,resource_id, first_name, first_name_reversed, last_name, last_name_reversed,  full_name, full_name_reversed, last_name_first_name, country_code) VALUES";
            /**
             * combine values
             */
            int toIndex = ((currentIndex + INTERVAL) > totalSize ? totalSize : (currentIndex + INTERVAL));
            for (int index = currentIndex; index < toIndex; index++) {
                if (index != currentIndex)
                    query = query.append(",");
                query = query.append(QString("(:resource_table_id%0, :resource_id%1, :first_name%2, "
                                              ":first_name_reversed%3, :last_name%4, :last_name_reversed%5, "
                                              ":full_name%6, :full_name_reversed%7, :last_name_first_name%8, "
                                              ":country_code%9)")
                             .arg(index)
                             .arg(index)
                             .arg(index)
                             .arg(index)
                             .arg(index)
                             .arg(index)
                             .arg(index)
                             .arg(index)
                             .arg(index)
                             .arg(index));
            }

            qDebug() << "Query : " + query;
            sqlQuery.prepare(query);

            for (int index = currentIndex; index < toIndex; index++) {
                sqlQuery.bindValue(QString(":resource_table_id%1").arg(index) , householdTableIDs.at(index) );
                sqlQuery.bindValue(QString(":resource_id%1").arg(index) , householdIDs.at(index) );
                sqlQuery.bindValue(QString(":first_name%1").arg(index) , firstNames.at(index) );
                sqlQuery.bindValue(QString(":first_name_reversed%1").arg(index) , firstNameReverseds.at(index) );
                sqlQuery.bindValue(QString(":last_name%1").arg(index) , lastNames.at(index) );
                sqlQuery.bindValue(QString(":last_name_reversed%1").arg(index) , lastNameReverseds.at(index) );
                sqlQuery.bindValue(QString(":full_name%1").arg(index) , lastNameFirstNames.at(index) );
                sqlQuery.bindValue(QString(":full_name_reversed%1").arg(index) , fullNames.at(index) );
                sqlQuery.bindValue(QString(":last_name_first_name%1").arg(index) , fullNameReverseds.at(index) );
                sqlQuery.bindValue(QString(":country_code%1").arg(index) , countryCodes.at(index) );
            }


            // Note that no SQL Statement is passed to 'exec' as it is a prepared statement.
            if (sqlQuery.exec()) {
                sqlQuery.finish();
            } else {
                const QSqlError error = sqlQuery.lastError();
                qDebug() << "Insert Search Household error: " + error.text();
                sqlQuery.finish();
                database.close();
                return false;
            }
            currentIndex += INTERVAL;
        }
        database.close();
        return true;
    }
}

bool CRUDSearchHouseholdTable::deleteAll()
{

    bool result = false;

    QSqlDatabase database = SQLConnection();

    if (!database.tables().contains("search_household")) {
        qDebug() << "Create record error: search_household table does not exist.";
        result = false;
    } else {

        qDebug() << "Deleting from database";
        QSqlQuery query(database);
        query.prepare("DELETE FROM search_household");

        // Note that no SQL Statement is passed to 'exec' as it is a prepared statement.
        if (query.exec()) {
            qDebug() << "Records deleted";
            result = true;

        } else {
            const QSqlError error = query.lastError();
            qDebug() << "Delete record error: " + error.text();
            result = false;

        }


    }


    return result;

}


bool CRUDSearchHouseholdTable::deleteResource(QString resourceId)
{

    bool result = false;


    QSqlDatabase database = SQLConnection();

    if (!database.tables().contains("search_household")) {
        qDebug() << "Create record error: search_household table does not exist.";
        result = false;
    } else {

        QSqlQuery query(database);

        // Note that no SQL Statement is passed to 'exec' as it is a prepared statement.
        if (query.exec("DELETE FROM search_household where resource_id match " + resourceId)) {
            result = true;

        } else {
            const QSqlError error = query.lastError();
            qDebug() << "Delete record error: " + error.text();
            result = false;

        }
        query.finish();
    }


    return result;

}


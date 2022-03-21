/*
 * CRUDResourceTable.cpp
 *
 *  Created on: 14/06/2016
 *      Author: Lucas Bento
 */


#include "CRUDSearchSubdivisionTable.hpp"
#include <bb/data/JsonDataAccess>
#include "../api/APIUtil.hpp"
#define INTERVAL 240
using namespace bb::data;


CRUDSearchSubdivisionTable::CRUDSearchSubdivisionTable()
{
}

CRUDSearchSubdivisionTable::~CRUDSearchSubdivisionTable()
{
}
bool CRUDSearchSubdivisionTable::insertOrUpdate(
                        QString subdivisionTableID,
                        QString subdivisionID,
                        QString name,
                        QString countryCode
)
{

    bool result = false;


    QSqlDatabase database = SQLConnection();

    if (!database.tables().contains("search_subdivision")) {
        qDebug() << "Create record error: search_subdivision table does not exist.";
        result = false;
    } else {


        QSqlQuery query(database);
        query.prepare("INSERT OR REPLACE INTO search_subdivision (resource_table_id, resource_id, name, country_code)"
                "VALUES(:resource_table_id, :resource_id, :name, :countryCode) ");

        query.bindValue(":resource_table_id", subdivisionTableID.toInt() );
        query.bindValue(":resource_id", subdivisionID.toInt() );
        query.bindValue(":name", name);
        query.bindValue(":countryCode", countryCode);

        // Note that no SQL Statement is passed to 'exec' as it is a prepared statement.
        if (query.exec()) {
            result = true;

        } else {
            const QSqlError error = query.lastError();
            qDebug() << "Create record error: " + error.text();
            result = false;

        }


    }


    return result;

}
bool CRUDSearchSubdivisionTable::insertOrUpdateBatch(
                        QList<QString> subdivisionTableIDs,
                        QList<QString> subdivisionIDs,
                        QList<QString> names,
                        QList<QString> countryCodes
) {
    bool result = false;

    QSqlDatabase database = SQLConnection();

    if (!database.tables().contains("search_subdivision")) {
        qDebug() << "Create record error: search_subdivision table does not exist.";
        result = false;
    } else {
        int totalSize = subdivisionTableIDs.size();
        int currentIndex = 0;
        while (currentIndex < totalSize) {
            QSqlQuery sqlQuery(database);
            QString query = "INSERT OR REPLACE INTO search_subdivision (resource_table_id, resource_id, name, country_code) VALUES";
            /**
             * combine values
             */
            int toIndex = ((currentIndex + INTERVAL) > totalSize ? totalSize : (currentIndex + INTERVAL));
            for (int index = currentIndex; index < toIndex; index++) {
                if (index != currentIndex)
                    query = query.append(",");
                query = query.append(QString("(:resource_table_id%0, :resource_id%1, :name%2, :countryCode%3)")
                             .arg(index)
                             .arg(index)
                             .arg(index)
                             .arg(index));
            }

            qDebug() << "Query : " + query;
            sqlQuery.prepare(query);

            for (int index = currentIndex; index < toIndex; index++) {
                sqlQuery.bindValue(QString(":resource_table_id%1").arg(index) , subdivisionTableIDs.at(index) );
                sqlQuery.bindValue(QString(":resource_id%1").arg(index) , subdivisionIDs.at(index) );
                sqlQuery.bindValue(QString(":name%1").arg(index) , names.at(index) );
                sqlQuery.bindValue(QString(":countryCode%1").arg(index) , countryCodes.at(index) );
            }

            // Note that no SQL Statement is passed to 'exec' as it is a prepared statement.
            if (sqlQuery.exec()) {
                result = true;
                sqlQuery.finish();
            } else {
                const QSqlError error = sqlQuery.lastError();
                qDebug() << "Create record error: " + error.text();
                sqlQuery.finish();
                database.close();
                return false;
            }

            currentIndex += INTERVAL;
        }

    }
    database.close();
    return result;
}

bool CRUDSearchSubdivisionTable::deleteResource(QString resourceId)
{

    bool result = false;


    QSqlDatabase database =  SQLConnection();

    if (!database.tables().contains("search_subdivision")) {
        qDebug() << "Create record error: search_subdivision table does not exist.";
        result = false;
    } else {

        qDebug() << "Deleting from database";
        QSqlQuery query(database);
        query.prepare("DELETE FROM search_subdivision where resource_id = " + resourceId);

        query.exec();

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

bool CRUDSearchSubdivisionTable::deleteAll()
{

    bool result = false;


    QSqlDatabase database = SQLConnection();

    if (!database.tables().contains("search_subdivision")) {
        qDebug() << "Create record error: search_subdivision table does not exist.";
        result = false;
    } else {

        qDebug() << "Deleting from database";
        QSqlQuery query(database);
        query.prepare("DELETE FROM search_subdivision");

        query.exec();

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


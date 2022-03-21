/*
 * CRUDAboutTable.cpp
 *
 *  Created on: 13/07/2016
 *      Author: Lucas Bento
 */


#include "CRUDAboutTable.hpp"
#include <bb/data/JsonDataAccess>
#include "../api/APIUtil.hpp"

using namespace bb::data;


CRUDAboutTable::CRUDAboutTable()
{
}

CRUDAboutTable::~CRUDAboutTable()
{
}

int CRUDAboutTable::getVersion()
{
    int version = -1;

    QSqlDatabase database = SQLConnection();

    if (!database.tables().contains("about")) {
        qDebug() << "About table does not exist.";
    } else {

        QSqlQuery query(database);
        query.prepare("SELECT version FROM about where ID = 1");

        // Note that no SQL Statement is passed to 'exec' as it is a prepared statement.
        if (query.exec()) {

            if (query.next()) {

                QSqlRecord rec = query.record();
                version = rec.value(0).toInt();
            }

        } else {
            const QSqlError error = query.lastError();
            qDebug() << "Get resource error: " + error.text();

        }
        query.finish();
    }

    return version;
}

QString CRUDAboutTable::getLastUpdated()
{
    QString lastUpdated = "";

    QSqlDatabase database = SQLConnection();

    if (!database.tables().contains("about")) {
        qDebug() << "About table does not exist.";
    } else {

        QSqlQuery query(database);
        query.prepare("SELECT last_sync FROM about where ID = 1");

        // Note that no SQL Statement is passed to 'exec' as it is a prepared statement.
        if (query.exec()) {

            if (query.next()) {

                QSqlRecord rec = query.record();
                lastUpdated = rec.value(0).toDateTime().toString("yyyy-MM-dd'T'HH:mm:ss.'000Z'");
            }

        } else {
            const QSqlError error = query.lastError();
            qDebug() << "Get resource error: " + error.text();

        }
        query.finish();
    }


    return lastUpdated;
}

QDateTime CRUDAboutTable::getLastUpdatedDateTime()
{
    QDateTime lastUpdated = QDateTime::currentDateTimeUtc();

    QSqlDatabase database = QSqlDatabase::database();

    if (!database.tables().contains("about")) {
        qDebug() << "About table does not exist.";
    } else {

        QSqlQuery query(database);
        query.prepare("SELECT last_sync FROM about where ID = 1");

        // Note that no SQL Statement is passed to 'exec' as it is a prepared statement.
        if (query.exec()) {

            if (query.next()) {

                QSqlRecord rec = query.record();
                lastUpdated = rec.value(0).toDateTime();
            }

        } else {
            const QSqlError error = query.lastError();
            qDebug() << "Get resource error: " + error.text();

        }
        query.finish();
    }

    database.close();
    return lastUpdated;
}
void CRUDAboutTable::setLastUpdatedNow()
{
    QString lastUpdated = "";

    QSqlDatabase database = QSqlDatabase::database();

    if (!database.tables().contains("about")) {
        qDebug() << "About table does not exist.";
    } else {

        QSqlQuery query(database);
        query.prepare("update about set last_sync = DateTime('now');");

        // Note that no SQL Statement is passed to 'exec' as it is a prepared statement.
        if (query.exec()) {


        } else {
            const QSqlError error = query.lastError();
            qDebug() << "Get resource error: " + error.text();

        }
        query.finish();
    }

    database.close();
}


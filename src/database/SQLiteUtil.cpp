/*
 * SQLiteUtil.cpp
 *
 *  Created on: 09/06/2016
 *      Author: Lucas
 */

#include "SQLiteUtil.hpp"
#include <bb/data/JsonDataAccess>
#include "CRUDBase.hpp"
#include <QtCore/QFile>
#include "APIUtil.hpp"

using namespace bb::data;

bool SQLiteUtil::openConnection()
{
    bool success = false;

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    // 2. Set the path of where the database will be located.
    //    Note: The db extension is not required
    database.setDatabaseName(DATABASE_PATH);

    // 3. Open a connection to the database, if the database does not exist
    //    one will be created if permitted.
    if (database.open()) {
        qDebug() << ("Database created/registered.");
        success = true;
    } else {
        // If the database fails to open, error information can be accessed via
        // the lastError function.
        const QSqlError error = database.lastError();
        qDebug() << "Error opening connection to the database: " + error.text();
    }

    // 4. Close the connection to the database.
    //    Be warned, closing the database will invalidate any SqlQuery objects (see below)
    database.close();

    return success;
}

bool SQLiteUtil::closeConnection()
{

    QSqlDatabase database = QSqlDatabase::database();
    database.close();
    return true;

}

bool SQLiteUtil::initDatabase(bool forceReplaceDb)
{

    SQLiteUtil::checkDatabaseExists(forceReplaceDb);

    if (SQLiteUtil::openConnection())
        return SQLiteUtil::databaseSetup();
    else
        return false;
}

void SQLiteUtil::checkDatabaseExists(bool forceReplaceDb)
{

    bool ok = true;
    if (!forceReplaceDb) {
        if (SQLiteUtil::openConnection()) {

            CRUDAboutTable mCRUDAboutTable;

            if (CRUDBase::databaseVersion() == mCRUDAboutTable.getVersion()) {
                ok = false;
            }
            SQLiteUtil::closeConnection();

        }
    }

    if (ok || forceReplaceDb) {

        QFile file(CONNECT_EXTERN_DATABASE_PATH);

        if (file.exists()) {

            qDebug() << "Starting Copying";
            QFile file1(DATABASE_PATH);
            if (file1.exists())
                ok = file1.remove();

            if (ok) {
                file.copy(DATABASE_PATH);
            }

        } else {
            QString t = "4";
            t = (ok ? "" : "");
        }
    }
}

// Synchronous Database Functionality with QSqlDatabase and QSqlQuery
bool SQLiteUtil::databaseSetup()
{

    bool result = true;
    QSqlDatabase database = QSqlDatabase::database();
    QSqlQuery query(database);
    query.exec(APIUtil::dbUnlock);
    query.prepare("CREATE TABLE IF NOT EXISTS resource ( "
            "                id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "                resource_type INTEGER, "
            "                resource_description VARCHAR, "
            "                resource_ad_description VARCHAR, "
            "                resource_json VARCHAR, "
            "                resource_thumbnail_id VARCHAR, "
            "                resource_country VARCHAR, "
            "                resource_country_name VARCHAR, "
            "                resource_locality INTEGER, "
            "                resource_locality_name VARCHAR, "
            "                resource_subdivision INTEGER, "
            "                resource_subdivision_name VARCHAR, "
            "                resource_id VARCHAR "
            ");");

    if (query.exec()) {
        qDebug() << "Table creation query executed successfully";
        result = true;
    } else {
        const QSqlError error = query.lastError();
        qDebug() << "Create table error:" + error.text();
        result = false;
    }
    query.finish();

    //  ABOUT
    query.prepare("CREATE TABLE IF NOT EXISTS about ("
            "                id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "                version INTEGER, "
            "                last_sync DATETIME "
            ");");

    if (query.exec()) {
        qDebug() << "Table creation query executed successfully";
        result = true;
    } else {
        const QSqlError error = query.lastError();
        qDebug() << "Create table error:" + error.text();
        result = false;
    }
    query.finish();

    // ABOUT REG
    query.prepare("INSERT INTO about"
            "                (id,version) values(1," + QString::number(DATABASE_VERSION) + ");");
    if (query.exec()) {
        qDebug() << "Reg. inserted";
        result = true;
    } else {
        const QSqlError error = query.lastError();
        qDebug() << "Create table error:" + error.text();
        result = true;
    }
    query.finish();

    // QUERY1
    query.prepare("CREATE UNIQUE INDEX IF NOT EXISTS res_idx on resource"
            "                (resource_type,resource_id);");

    if (query.exec()) {
        qDebug() << "Table creation query executed successfully";
        result = true;
    } else {
        const QSqlError error = query.lastError();
        qDebug() << "Create table error:" + error.text();
        result = false;
    }
    query.finish();
    // QUERY2
    query.prepare("CREATE INDEX IF NOT EXISTS res_idx1 on resource"
            "                (resource_country);");

    if (query.exec()) {
        qDebug() << "Table creation query executed successfully";
        result = true;
    } else {
        const QSqlError error = query.lastError();
        qDebug() << "Create table error:" + error.text();
        result = false;
    }
    query.finish();
    // QUERY3
    query.prepare("CREATE INDEX IF NOT EXISTS res_idx2 on resource"
            "                (resource_locality);");

    if (query.exec()) {
        qDebug() << "Table creation query executed successfully";
        result = true;
    } else {
        const QSqlError error = query.lastError();
        qDebug() << "Create table error:" + error.text();
        result = false;
    }
    query.finish();
    // QUERY4
    query.prepare("CREATE INDEX IF NOT EXISTS res_idx3 on resource"
            "                (resource_subdivision);");

    if (query.exec()) {
        qDebug() << "Table creation query executed successfully";
        result = true;
    } else {
        const QSqlError error = query.lastError();
        qDebug() << "Create table error:" + error.text();
        result = false;
    }
    query.finish();
    // QUERY5
    query.prepare("CREATE INDEX IF NOT EXISTS res_idx4 on resource"
            "                (resource_type);");

    if (query.exec()) {
        qDebug() << "Table creation query executed successfully";
        result = true;
    } else {
        const QSqlError error = query.lastError();
        qDebug() << "Create table error:" + error.text();
        result = false;
    }
    query.finish();
    // QUERY6
    query.prepare("CREATE INDEX IF NOT EXISTS res_idx5 on resource"
            "                (resource_type,resource_locality);");

    if (query.exec()) {
        qDebug() << "Table creation query executed successfully";
        result = true;
    } else {
        const QSqlError error = query.lastError();
        qDebug() << "Create table error:" + error.text();
        result = false;
    }
    query.finish();
    // QUERY7
    query.prepare("CREATE INDEX IF NOT EXISTS res_idx6 on resource"
            "                (resource_id);");

    if (query.exec()) {
        qDebug() << "Table creation query executed successfully";
        result = true;
    } else {
        const QSqlError error = query.lastError();
        qDebug() << "Create table error:" + error.text();
        result = false;
    }
    query.finish();
    // QUERY8
    query.prepare("CREATE INDEX IF NOT EXISTS res_idx7 on resource"
            "                (resource_type,resource_subdivision);");

    if (query.exec()) {
        qDebug() << "Table creation query executed successfully";
        result = true;
    } else {
        const QSqlError error = query.lastError();
        qDebug() << "Create table error:" + error.text();
        result = false;
    }
    query.finish();
    // QUERY9
    query.prepare("CREATE INDEX IF NOT EXISTS res_idx8 on resource"
            "                (resource_type,resource_country);");

    if (query.exec()) {
        qDebug() << "Table creation query executed successfully";
        result = true;
    } else {
        const QSqlError error = query.lastError();
        qDebug() << "Create table error:" + error.text();
        result = false;
    }
    query.finish();
    // QUERY9
    query.prepare("CREATE INDEX IF NOT EXISTS res_idx9 on resource"
            "                (resource_type,resource_description);");

    if (query.exec()) {
        qDebug() << "Table creation query executed successfully";
        result = true;
    } else {
        const QSqlError error = query.lastError();
        qDebug() << "Create table error:" + error.text();
        result = false;
    }
    query.finish();
    // QUERY10
    query.prepare("CREATE INDEX IF NOT EXISTS res_idx10 on resource"
            "                (resource_type,resource_ad_description);");

    if (query.exec()) {
        qDebug() << "Table creation query executed successfully";
        result = true;
    } else {
        const QSqlError error = query.lastError();
        qDebug() << "Create table error:" + error.text();
        result = false;
    }
    query.finish();
    // QUERY11
    query.prepare("CREATE INDEX IF NOT EXISTS res_idx11 on resource"
            "                (resource_type,resource_description,resource_ad_description);");

    if (query.exec()) {
        qDebug() << "Table creation query executed successfully";
        result = true;
    } else {
        const QSqlError error = query.lastError();
        qDebug() << "Create table error:" + error.text();
        result = false;
    }
    query.finish();
    // IDX12
    query.prepare("CREATE INDEX IF NOT EXISTS res_idx12 on resource"
            "                (resource_type,resource_subdivision,resource_description);");

    if (query.exec()) {
        qDebug() << "Table creation query executed successfully";
        result = true;
    } else {
        const QSqlError error = query.lastError();
        qDebug() << "Create table error:" + error.text();
        result = false;
    }
    query.finish();
    // IDX13
    query.prepare("CREATE INDEX IF NOT EXISTS res_idx13 on resource"
            "                (resource_type,resource_locality,resource_description);");

    if (query.exec()) {
        qDebug() << "Table creation query executed successfully";
        result = true;
    } else {
        const QSqlError error = query.lastError();
        qDebug() << "Create table error:" + error.text();
        result = false;
    }
    query.finish();
    // QUERY12 - HOUSEHOLD SEARCH VIRTUAL TABLE - reversed fields in orde to search the end of words
    query.prepare(
            "CREATE VIRTUAL TABLE  IF NOT EXISTS search_household USING fts4"
                    "                (resource_table_id, resource_id, first_name, first_name_reversed, last_name, last_name_reversed, full_name, full_name_reversed, last_name_first_name, country_code, tokenize=unicode61);");

    if (query.exec()) {
        qDebug() << "fts4 Table creation query executed successfully";
        result = true;
    } else {
        const QSqlError error = query.lastError();
        qDebug() << "Create table error:" + error.text();
        result = false;
    }
    query.finish();

    // QUERY13 - LOCALITY SEARCH VIRTUAL TABLE
    query.prepare("CREATE VIRTUAL TABLE IF NOT EXISTS search_locality USING fts4"
            "(resource_table_id, resource_id, name, country_code, tokenize=unicode61);");

    if (query.exec()) {
        qDebug() << "fts4 Table creation query executed successfully";
        result = true;
    } else {
        const QSqlError error = query.lastError();
        qDebug() << "Create table error:" + error.text();
        result = false;
    }
    query.finish();
    // QUERY14 - SUBDIVISION SEARCH VIRTUAL TABLE
    query.prepare(
            "CREATE VIRTUAL TABLE IF NOT EXISTS search_subdivision USING fts4"
                    "                (resource_table_id, resource_id, name, country_code, tokenize=unicode61);");

    if (query.exec()) {
        qDebug() << "fts4Table creation query executed successfully";
        result = true;
    } else {
        const QSqlError error = query.lastError();
        qDebug() << "Create table error:" + error.text();
        result = false;
    }
    query.finish();

    // close the database connection
    database.close();

    return result;
}

void SQLiteUtil::wipeDb()
{

    QSqlDatabase database = QSqlDatabase::database();
    QSqlQuery query(database);
//    query.exec(APIUtil::dbUnlock);

    //sql
    query.prepare("DROP INDEX IF EXISTS res_idx;");

    if (query.exec()) {
        qDebug() << "Dropped index";
    } else {
        const QSqlError error = query.lastError();
        qDebug() << "Drop table error:" + error.text();
    }

    query.finish();

    //sql1
    query.prepare("DROP TABLE IF EXISTS resource;");
    if (query.exec()) {
        qDebug() << "Dropped table";
    } else {
        const QSqlError error = query.lastError();
        qDebug() << "Drop table error:" + error.text();
    }

    query.finish();
    //sql2
    query.prepare("DROP TABLE IF EXISTS search_household;");
    if (query.exec()) {
        qDebug() << "Dropped table";
    } else {
        const QSqlError error = query.lastError();
        qDebug() << "Drop table error:" + error.text();
    }
    //sql2
    query.prepare("DROP TABLE IF EXISTS search_locality;");
    if (query.exec()) {
        qDebug() << "Dropped table";
    } else {
        const QSqlError error = query.lastError();
        qDebug() << "Drop table error:" + error.text();
    }
    //sql3
    query.prepare("DROP TABLE IF EXISTS search_subdivision;");
    if (query.exec()) {
        qDebug() << "Dropped table";
    } else {
        const QSqlError error = query.lastError();
        qDebug() << "Drop table error:" + error.text();
    }
    query.finish();

    database.close();

}

QString SQLiteUtil::getReversed(QString str)
{
    QString reversed = "";
    int leng = str.count();

    for (int i = leng - 1; i >= 0; i--) {
        reversed = reversed + str[i];
    }

    return reversed;
}

QString SQLiteUtil::getTypeDescription(int resType)
{

    switch (resType) {
        case ResourceType::Locality:
            return "Locality";
        case ResourceType::Household:
            return "Household";
        case ResourceType::Subdivision:
            return "Subdivision";
        case ResourceType::Country:
            return "Country";
        case ResourceType::Interchange:
            return "Interchange";
        case ResourceType::CurrentUser:
            return "CurrentUser";
        default:
            return "";
    }
}

QString SQLiteUtil::getTypeDescriptionSearch(int resType)
{

    switch (resType) {
        case ResourceType::Locality:
            return "Locality";
        case ResourceType::Household:
            return "Member";
        case ResourceType::Subdivision:
            return "Subdivision";
        default:
            return "";
    }

}

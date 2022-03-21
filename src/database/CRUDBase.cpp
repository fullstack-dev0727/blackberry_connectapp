

#include "CRUDBase.hpp"
#include <bb/data/JsonDataAccess>
#include <QtSql/QtSql>
#include "SQLiteUtil.hpp"

using namespace bb::data;

CRUDBase::CRUDBase()
{

}
CRUDBase::~CRUDBase()
{
    if (m_connection.isOpen()) {
        QSqlDatabase::removeDatabase(DATABASE_PATH);
        m_connection.removeDatabase(DATABASE_DRIVER);
    }
}

int CRUDBase::databaseVersion() {
    return DATABASE_VERSION;
}
QSqlDatabase& CRUDBase::SQLConnection()
{
    if (m_connection.isOpen()) {
        return m_connection;
    }

    if (QSqlDatabase::contains(DATABASE_CONNECTION_NAME)){
        // if the database connection already exists, then reuse it
        // Calling this also calls "open"
        m_connection = QSqlDatabase::database(DATABASE_CONNECTION_NAME);

        if (!m_connection.isOpen()){
            qWarning() << "Could not open connection to database: " << m_connection.lastError().text();
        }
    } else {
            // Otherwise, the connection doesn't exist, so create it and open it
            m_connection = QSqlDatabase::addDatabase(DATABASE_DRIVER, DATABASE_CONNECTION_NAME);
            m_connection.setDatabaseName(DATABASE_PATH);

            if (!m_connection.isValid()) {
                qDebug() << "Could not set data base name probably due to invalid driver.";
            } else if (!m_connection.open()) {
                qWarning() << "Could not open connection to database: " << m_connection.lastError().text();
            }
    }

    return m_connection;
}

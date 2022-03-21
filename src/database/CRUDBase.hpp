/*
 * SQLiteUtil.hpp
 *
 *  Created on: 09/06/2016
 *      Author: Lucas
 */

#ifndef CRUDBASE_HPP_
#define CRUDBASE_HPP_



#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/OrientationSupport>
#include <bb/system/SystemDialog>

//Crud
#include "../ResourceType.h"
#include <QDateTime>

#include <QtSql/QtSql>

using namespace bb::cascades;
using namespace bb::system;
//using namespace bb::data;

#define DATABASE_PATH "./data/connect.sqlite"
#define CONNECT_EXTERN_DATA_PATH "/accounts/1000/removable/sdcard/documents/connect_data"
#define CONNECT_EXTERN_DATABASE_PATH "/sdcard/Music/connect.sqlite" //"/accounts/1000/removable/sdcard/documents/connect_data/connect.sqlite"
#define CONNECT_EXTERN_IMAGE_PATH "/sdcard/Music/images" //"/accounts/1000/removable/sdcard/documents/connect_data/images"
#define DATABASE_DRIVER "QSQLITE"
#define DATABASE_CONNECTION_NAME "database_connection"
#define DATABASE_VERSION 9

class CRUDBase
{
public:
    CRUDBase();
    virtual ~CRUDBase();
    QSqlDatabase& SQLConnection();

    static int databaseVersion();
private:
    QSqlDatabase m_connection;

};


#endif /* CRUDBASE_HPP_ */

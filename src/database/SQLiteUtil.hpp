/*
 * SQLiteUtil.hpp
 *
 *  Created on: 09/06/2016
 *      Author: Lucas
 */

#ifndef SQLITEUTIL_HPP_
#define SQLITEUTIL_HPP_



#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/OrientationSupport>
#include <bb/system/SystemDialog>

//Crud
#include "CRUDAboutTable.hpp"
#include "CRUDResourceTable.hpp"
#include "CRUDSearchHouseholdTable.hpp"
#include "CRUDSearchLocalityTable.hpp"
#include "CRUDSearchSubdivisionTable.hpp"
#include "../ResourceType.h"
#include <QDateTime>

#include <QtSql/QtSql>

using namespace bb::cascades;
using namespace bb::system;


class SQLiteUtil
{
public:
    //function
    static QString getReversed(QString str);

    static bool openConnection();
    static bool closeConnection();

    static bool initDatabase(bool forceReplaceDb);
    static bool databaseSetup();

    static QString getTypeDescription(int resType);
    static QString getTypeDescriptionSearch(int resType);

    static void cleanDb();
    static void wipeDb();

    static void checkDatabaseExists(bool forceReplaceDb);

private:

};


#endif /* SQLITEUTIL_HPP_ */

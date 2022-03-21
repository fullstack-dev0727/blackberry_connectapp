/*
 * CrudResourceTable.hpp
 *
 *  Created on: 14/06/2016
 *      Author: Lucas
 */

#ifndef CRUDABOUTTABLE_HPP_
#define CRUDABOUTTABLE_HPP_


#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/OrientationSupport>
#include <bb/system/SystemDialog>
#include <QtSql/QtSql>
#include <QDateTime>
#include "SQLiteUtil.hpp"
#include "CRUDBase.hpp"

using namespace bb::cascades;
using namespace bb::system;


class CRUDAboutTable : public CRUDBase
{
public:
    CRUDAboutTable();
    virtual ~CRUDAboutTable();


    int getVersion() ;
    QString getLastUpdated() ;
    QDateTime getLastUpdatedDateTime();

    void setLastUpdatedNow();
};




#endif /* CRUDABOUTTABLE_HPP_ */

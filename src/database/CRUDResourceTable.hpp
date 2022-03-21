/*
 * CrudResourceTable.hpp
 *
 *  Created on: 14/06/2016
 *      Author: Lucas
 */

#ifndef CRUDRESOURCETABLE_HPP_
#define CRUDRESOURCETABLE_HPP_


#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/OrientationSupport>
#include <bb/system/SystemDialog>
#include "../ResourceType.h"
#include <QtSql/QtSql>
#include "SQLiteUtil.hpp"
#include "CRUDBase.hpp"

using namespace bb::cascades;
using namespace bb::system;


class CRUDResourceTable : public CRUDBase
{
public:
    CRUDResourceTable();
    virtual ~CRUDResourceTable();

    QVariantMap* getResource(int restType, QString resId) ;
    QString getResources(int resType, QString resLocality, QString resSubdivision, QString resCountry,  int page) ;
    int getResourcesCount(int resType, QString resLocality, QString resSubdivision, QString resCountry) ;
    QString searchResources(QString searchTerm, QString resTypeList, QString resCountry, int page);

    int insertOrUpdate(QString resourceID,
                        int resourceType,
                        QString resourceDescription,
                        QString resourceAdDescription,
                        QString resourceJson,
                        QString resourceThumbnailId,
                        QString resourceCountry,
                        QString resourceCountryName,
                        int resourceLocality,
                        QString resourceLocalityName,
                        int resourceSubdivision,
                        QString resourceSubdivisionName
                      );
    QList<int> insertOrUpdateBatch(QList<QString> resourceIDs,
                                        QList<int> resourceTypes,
                                        QList<QString> resourceDescriptions,
                                        QList<QString> resourceAdDescriptions,
                                        QList<QString> resourceJsons,
                                        QList<QString> resourceThumbnailIds,
                                        QList<QString> resourceCountrys,
                                        QList<QString> resourceCountryNames,
                                        QList<int> resourceLocalitys,
                                        QList<QString> resourceLocalityNames,
                                        QList<int> resourceSubdivisions,
                                        QList<QString> resourceSubdivisionNames
                                  );

    bool deleteAll(int resType);

    bool deleteResource(int resType, QString resourceId);

};




#endif /* CRUDRESOURCETABLE_HPP_ */

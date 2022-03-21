/*
 * CRUDResourceTable.cpp
 *
 *  Created on: 14/06/2016
 *      Author: Lucas Bento
 */


#include "CRUDResourceTable.hpp"
#include <bb/data/JsonDataAccess>
#include "../api/APIUtil.hpp"
#define INTERVAL 80

using namespace bb::data;

CRUDResourceTable::CRUDResourceTable()
{
}

CRUDResourceTable::~CRUDResourceTable()
{
}
QList<int> CRUDResourceTable::insertOrUpdateBatch(QList<QString> resourceIDs,
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
                              ) {
    QList<int> results;

    QSqlDatabase database = SQLConnection();
    /**
     * check whether resource table is existed or not
     */
    if (!database.tables().contains("resource")) {
            qDebug() << "Create record error: resource table does not exist.";
    } else {

        int totalSize = resourceIDs.size();
        int currentIndex = 0;
        while (currentIndex < totalSize) {
            QSqlQuery sqlQuery(database);
            QString query = "INSERT OR REPLACE INTO resource (resource_id, resource_type, resource_description, resource_ad_description, resource_json, resource_thumbnail_id, resource_country, resource_country_name, resource_locality, resource_locality_name, resource_subdivision, resource_subdivision_name) VALUES";
            /**
             * combine values
             */
            int toIndex = ((currentIndex + INTERVAL) > totalSize ? totalSize : (currentIndex + INTERVAL));
            for (int index = currentIndex; index < toIndex; index++) {
                if (index != currentIndex)
                    query = query.append(",");
                query = query.append(QString("(:resourceId%0, :resourceType%1, :resourceDescription%2, "
                                              ":resourceAdDescription%3, :resourceJson%4, :resourceThumbnailId%5, "
                                              ":resourceCountry%6, :resourceCountryName%7, :resourceLocality%8, "
                                              ":resourceLocalityName%9, :resourceSubdivision%10, :resourceSubdivisionName%11)")
                             .arg(index)
                             .arg(index)
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
                sqlQuery.bindValue(QString(":resourceId%0").arg(index) , resourceIDs.at(index) );
                sqlQuery.bindValue(QString(":resourceType%0").arg(index) , resourceTypes.at(index) );
                sqlQuery.bindValue(QString(":resourceDescription%0").arg(index) , resourceDescriptions.at(index) );
                sqlQuery.bindValue(QString(":resourceAdDescription%0").arg(index) , resourceAdDescriptions.at(index) );
                sqlQuery.bindValue(QString(":resourceJson%0").arg(index) , resourceJsons.at(index) );
                sqlQuery.bindValue(QString(":resourceThumbnailId%0").arg(index) , resourceThumbnailIds.at(index) );
                sqlQuery.bindValue(QString(":resourceCountry%0").arg(index) , resourceCountrys.at(index) );
                sqlQuery.bindValue(QString(":resourceCountryName%0").arg(index) , resourceCountryNames.at(index) );
                sqlQuery.bindValue(QString(":resourceLocality%0").arg(index) , resourceLocalitys.at(index) );
                sqlQuery.bindValue(QString(":resourceLocalityName%0").arg(index) , resourceLocalityNames.at(index) );
                sqlQuery.bindValue(QString(":resourceSubdivision%0").arg(index) , resourceSubdivisions.at(index) );
                sqlQuery.bindValue(QString(":resourceSubdivisionName%0").arg(index) , resourceSubdivisionNames.at(index) );
            }

            // Note that no SQL Statement is passed to 'exec' as it is a prepared statement.
            if (sqlQuery.exec()) {
                sqlQuery.prepare(QString("SELECT id FROM resource ORDER BY id DESC LIMIT %1").arg(toIndex - currentIndex));
                // Note that no SQL Statement is passed to 'exec' as it is a prepared statement.
                if (sqlQuery.exec()) {
                    QList<int> sublist;
                    while (sqlQuery.next()) {
                        QSqlRecord rec = sqlQuery.record();
                        int id = rec.value(0).toInt();
                        sublist.append(id);
                    }
                    if (sublist.size() > 1)
                        std::reverse(sublist.begin(), sublist.end());
                    results.append(sublist);
                } else {
                    const QSqlError error = sqlQuery.lastError();
                    qDebug() << "Get ids error: " + error.text();
                }
            } else {
                const QSqlError error = sqlQuery.lastError();
                qDebug() << "Insert Resource error: " + error.text();
            }
            currentIndex += INTERVAL;
            sqlQuery.finish();
        }
        database.close();
    }
    return results;
}
int CRUDResourceTable::insertOrUpdate(QString resourceID,
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
)
{

    int result = 0;

    QSqlDatabase database = SQLConnection();

    if (!database.tables().contains("resource")) {
        qDebug() << "Create record error: resource table does not exist.";
        result = false;
    } else {

        QSqlQuery query(database);
        query.prepare("INSERT OR REPLACE INTO resource (resource_id, resource_type, resource_description, resource_ad_description, "
                //query.prepare("INSERT INTO resource (resource_id, resource_type, resource_description, resource_ad_description, "
                "resource_json, resource_thumbnail_id, resource_country, resource_country_name, resource_locality, resource_locality_name, resource_subdivision, resource_subdivision_name) "
                "VALUES(:resourceId, :resourceType, :resourceDescription, "
                ":resourceAdDescription, :resourceJson, :resourceThumbnailId, :resourceCountry, :resourceCountryName,  :resourceLocality, :resourceLocalityName, :resourceSubdivision, :resourceSubdivisionName)" );

        query.bindValue(":resourceId", resourceID );
        query.bindValue(":resourceType", resourceType);
        query.bindValue(":resourceDescription", resourceDescription);
        query.bindValue(":resourceAdDescription", resourceAdDescription);
        query.bindValue(":resourceJson", resourceJson);
        query.bindValue(":resourceThumbnailId", resourceThumbnailId);
        query.bindValue(":resourceCountry", resourceCountry);
        query.bindValue(":resourceCountryName", resourceCountryName);
        query.bindValue(":resourceLocality", resourceLocality);
        query.bindValue(":resourceLocalityName", resourceLocalityName);
        query.bindValue(":resourceSubdivision", resourceSubdivision);
        query.bindValue(":resourceSubdivisionName", resourceSubdivision);

        // Note that no SQL Statement is passed to 'exec' as it is a prepared statement.
        if (query.exec()) {

            result = query.lastInsertId().toInt();

        } else {
            const QSqlError error = query.lastError();
            qDebug() << "Insert Resource error: " + error.text();
            result = 0;

        }
        query.finish();


    }


    return result;

}

bool CRUDResourceTable::deleteAll(int resType)
{

    bool result = false;


    QSqlDatabase database = SQLConnection();

    if (!database.tables().contains("resource")) {
        qDebug() << "Create record error: resource table does not exist.";
        result = false;
    } else {

        QString condition = "";
        if (resType > 0)
            condition = " WHERE resource_type = \"" + SQLiteUtil::getTypeDescription(resType) + "\"";

        qDebug() << "Deleting from database";
        QSqlQuery query(database);
        query.prepare("DELETE FROM resource" + condition);

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

bool CRUDResourceTable::deleteResource(int resType, QString resourceId)
{

    bool result = false;


    QSqlDatabase database = SQLConnection();

    if (!database.tables().contains("resource")) {
        qDebug() << "Create record error: resource table does not exist.";
        result = false;
    } else {

        QString condition = "";
        if (resType > 0)
            condition = QString(" WHERE resource_type = %1 and resource_id = %2").arg(QString::number(resType), resourceId) ;

        qDebug() << "Deleting from database";
        QSqlQuery query(database);
        query.prepare("DELETE FROM resource" + condition);

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
        query.finish();

    }

    return result;

}


QVariantMap* CRUDResourceTable::getResource(int resType, QString resId)
{

    QVariantMap *pResult = new QVariantMap();
    QSqlDatabase database = SQLConnection();
    QString countryList = "";
    bool hasFound = false;

    if (resType == ResourceType::Country )
        countryList = QString("\"ZZ\",%1").arg(AppSettings::getCurrentUserSubscribedCountries());
    else if (resType != ResourceType::CurrentUser )
        countryList = AppSettings::getCurrentUserSubscribedCountries();


    if (!database.tables().contains("resource")) {
        qDebug() << "Resource table does not exist.";
    } else {

        QString condition = "";
        QString restriction = "";

        if (resType > 0)
            condition = " WHERE  resource_type = " + QString::number(resType);

        if (!resId.isEmpty())
            condition = condition +  (condition.isEmpty() ? " WHERE " : " AND ") + " resource_id = \"" + resId + "\"";

        if (!countryList.isEmpty()) {
            restriction = QString("%1 resource_country in (%2) ").arg(condition.isEmpty() ? " WHERE " : " AND ", countryList);
        }


        QSqlQuery query(database);
        query.prepare(QString("SELECT * FROM resource %1 %2 ").arg(condition,restriction));

        //query.exec();

        // Note that no SQL Statement is passed to 'exec' as it is a prepared statement.
        if (query.exec()) {

            if (query.next()) {

                hasFound = true;
                QSqlRecord rec = query.record();
                int numFields = rec.count();
                for (int nField = 0; nField < numFields; nField++)
                {
                    QString key = rec.fieldName(nField);
                    QVariant value = rec.value(nField);
                    pResult->insert(key, value);
                }

            }

        } else {
            const QSqlError error = query.lastError();
            qDebug() << "Get resource error: " + error.text();

        }
        query.finish();


        //Check if it's just a permission problem
        if (!hasFound) {
            //TODO - Test if not found - then, do the query without restriction, if > 0. return no permisson message
            QSqlQuery query1(database);
            query1.prepare(QString("SELECT resource_id FROM resource %1 ").arg(condition));
            // Note that no SQL Statement is passed to 'exec' as it is a prepared statement.
            if (query1.exec()) {

                if (query1.next()) {
                    QString key = "no_permission";
                    QVariant value = "true";
                    pResult->insert(key, value);
                }
            }
            query1.finish();

        }


    }

    return pResult;
}


QString CRUDResourceTable::getResources(int resType, QString resLocality, QString resSubdivision, QString resCountry, int page)
{

    QVariantList listResult;
    QSqlDatabase database = SQLConnection();
    QString countryList = "";

    if (resType == ResourceType::CountryAll) {
        resType = ResourceType::Country;
        countryList = "\"ZZ\"";
    }


    if (resCountry.isEmpty() && resType != ResourceType::Interchange) {//There are no country info in interchn
        countryList = countryList + (countryList.isEmpty() ? "" : ",");
        countryList = countryList + AppSettings::getCurrentUserSubscribedCountries();
    }


    if (!database.tables().contains("resource")) {
        qDebug() << "Resource table does not exist.";
    } else {
        //paging
        QString paging = "";
        if (page > 0) {
            paging = " LIMIT " + QString::number(APIUtil::pageSize);
            if (page > 1)
                paging = paging +  " OFFSET " + QString::number(APIUtil::pageSize*(page-1));
        }


        QString condition = "";
        if (resType > 0)
            condition = " WHERE resource_type = " + QString::number(resType) ;

        if (!resLocality.isEmpty())
            condition = condition +  (condition.isEmpty() ? " WHERE " : " AND ") + " resource_locality = " + resLocality;

        if (!resSubdivision.isEmpty())
            condition = condition +  (condition.isEmpty() ? " WHERE " : " AND ") + " resource_subdivision = " + resSubdivision;

        if (!resCountry.isEmpty())
            condition = condition +  (condition.isEmpty() ? " WHERE " : " AND ") + " resource_country in ( \"" + resCountry + "\" )";
        else if (!countryList.isEmpty()) {
            condition = condition +  (condition.isEmpty() ? " WHERE " : " AND ") + " resource_country in ( " + countryList + " )";
        }




        QSqlQuery query(database);
        query.prepare("SELECT * FROM resource" + condition + " ORDER BY resource_description" + paging);


        //query.exec();

        qDebug() << "Exec - time: " + QTime::currentTime().toString("mm:ss.zzz");

        // Note that no SQL Statement is passed to 'exec' as it is a prepared statement.
        if (query.exec()) {

            qDebug() << "Finished - time: " + QTime::currentTime().toString("mm:ss.zzz");

            qDebug() << "While - time: " + QTime::currentTime().toString("mm:ss.zzz");
            while (query.next())  {

                QSqlRecord rec = query.record();
                int numFields = rec.count();
                for (int nField = 0; nField < numFields; nField++)
                {
                    if (rec.fieldName(nField) == "resource_json") {

                        QString st = rec.value(nField).toString();

                        st.replace("\r\n", "");
                        st.replace("''", "");
                        st.replace("\\", "[sub1][sub2]");
                        st.replace("\n", "");
                        st.replace("\"{", "{");
                        st.replace("}\"", "}");


                        listResult.append(st);
                        //JsonDataAccess dataAccess;
                        //listResult.append(dataAccess.loadFromBuffer(rec.value(nField).toString()).toMap());
                        break;
                    }
                }

            }
            qDebug() << "While - end: " + QTime::currentTime().toString("mm:ss.zzz");

        } else {
            const QSqlError error = query.lastError();
            qDebug() << "Get resource error: " + error.text();
        }




    }


    JsonDataAccess jda;

    QMap<QString, QVariant> map;
    map["Results"] = listResult;

    QString jsonBuffer1;
    jda.saveToBuffer(map, &jsonBuffer1);

    jsonBuffer1.replace("\r\n", "");
    jsonBuffer1.replace("''", "");
    jsonBuffer1.replace("\\", "");
    jsonBuffer1.replace("\n", "");
    jsonBuffer1.replace("\"{", "{");
    jsonBuffer1.replace("}\"", "}");
    jsonBuffer1.replace("[sub1]", "\\");
    jsonBuffer1.replace("[sub2]", "");


//    QFile textfile2("/accounts/1000/shared/documents/query2.txt");
//    textfile2.open(QIODevice::WriteOnly | QIODevice::Text);
//    QTextStream out2(&textfile2);
//    out2 << jsonBuffer1;
//    textfile2.close();



    return jsonBuffer1;
}


QString CRUDResourceTable::searchResources(QString searchTerm, QString resTypeList, QString resCountry, int page) {
    QString countryList = "";

    QVariantList listResult;
    QSqlDatabase database = SQLConnection();

    if (resCountry.isEmpty())
        countryList = AppSettings::getCurrentUserSubscribedCountries();


    if (!database.tables().contains("resource")) {
        qDebug() << "Resource table does not exist.";
    } else {
        //paging
        QString paging = "";
        if (page > 0) {
            paging = " LIMIT " + QString::number(APIUtil::pageSize);
            if (page > 1)
                paging = paging +  " OFFSET " + QString::number(APIUtil::pageSize*(page-1));
        }

        QString condition = "";
        if (!resCountry.isEmpty())
            condition = " AND S.country_code in ( \"" + resCountry + "\" )";
        else if (!countryList.isEmpty()) {
            condition = " AND S.country_code in ( " + countryList + " )";
        }

        //SEARCH DATARAW
        QString strQuery = "WITH dataraw AS ( ";

        if (resTypeList.compare("Locality,Subdivision") == 0 || resTypeList.isEmpty()) {
            strQuery = strQuery +
                    "SELECT " + QString::number(ResourceType::Subdivision) + " as type, 0 as sort, cast(S.resource_table_id AS INTEGER) as table_id FROM search_subdivision S"
                    " WHERE S.name MATCH \"" + searchTerm + "*\"" + condition +
                    " UNION "
                    "SELECT " + QString::number(ResourceType::Locality) +" as type, 0 as sort, cast(S.resource_table_id AS INTEGER) as table_id  FROM search_locality S"
                    " WHERE S.name MATCH \"" + searchTerm + "*\"" + condition;
        }
        if (resTypeList.compare("Member") == 0 || resTypeList.isEmpty()) {

            if (resTypeList.compare("Locality,Subdivision") == 0  || resTypeList.isEmpty())
                strQuery = strQuery + " UNION ";

            strQuery = strQuery +
                    "SELECT " + QString::number(ResourceType::Household) + " as type, 0 as sort, cast(S.resource_table_id AS INTEGER) as table_id FROM search_household S"
                    " WHERE S.last_name MATCH \"" + searchTerm + "*\"" + condition +
                    " UNION "
                    "SELECT " + QString::number(ResourceType::Household) + " as type, 1 as sort, cast(S.resource_table_id AS INTEGER) as table_id FROM search_household S"
                    " WHERE S.last_name_first_name MATCH \"" + searchTerm + "*\"" + condition +
                    " UNION "
                    "SELECT " + QString::number(ResourceType::Household) + " as type, 2 as sort, cast(S.resource_table_id AS INTEGER) as table_id FROM search_household S"
                    " WHERE S.first_name MATCH \"" + searchTerm + "*\"" + condition +
                    " UNION "
                    "SELECT " + QString::number(ResourceType::Household) + " as type, 3 as sort, cast(S.resource_table_id AS INTEGER) as table_id FROM search_household S"
                    " WHERE S.full_name MATCH \"" + searchTerm + "*\"" + condition +
                    " UNION "
                    "SELECT " + QString::number(ResourceType::Household) + " as type, 4 as sort, cast(S.resource_table_id AS INTEGER) as table_id FROM search_household S"
                    " WHERE S.last_name_reversed MATCH \"" + SQLiteUtil::getReversed(searchTerm) + "*\"" + condition +
                    " UNION "
                    "SELECT " + QString::number(ResourceType::Household) + " as type, 5 as sort, cast(S.resource_table_id AS INTEGER) as table_id FROM search_household S"
                    " WHERE S.first_name_reversed MATCH \"" + SQLiteUtil::getReversed(searchTerm) + "*\"" + condition;
        }

        strQuery = strQuery + " )";


        //distinct
        strQuery = strQuery +
                "  SELECT DISTINCT D.type, R.resource_type,R.resource_id, R.resource_description, R.resource_ad_description, resource_thumbnail_id, R.resource_json, R.resource_country_name, R.resource_locality_name"
                " FROM dataraw D"
                " INNER JOIN resource R on R.id = D.table_id"
                " ORDER BY D.type, D.sort, R.resource_description " + paging;



        QSqlQuery query(database);
        query.prepare(strQuery);




        QFile textfile("/accounts/1000/shared/documents/querySearch.txt");
        textfile.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&textfile);
        out << strQuery;
        textfile.close();

        //query.exec();

        qDebug() << "Exec - time: " + QTime::currentTime().toString("mm:ss.zzz");

        // Note that no SQL Statement is passed to 'exec' as it is a prepared statement.
        if (query.exec()) {

            qDebug() << "Finished - time: " + QTime::currentTime().toString("mm:ss.zzz");

            qDebug() << "While - time: " + QTime::currentTime().toString("mm:ss.zzz");
            while (query.next())  {

                QSqlRecord rec = query.record();
                int numFields = rec.count();


                QString type = "";
                QMap<QString, QVariant> mapRes;

                for (int nField = 0; nField < numFields; nField++)
                {

                    if (rec.fieldName(nField) == "resource_type") { //make sure the fields are in order
                        type = SQLiteUtil::getTypeDescriptionSearch(rec.value(nField).toInt());
                    }else if (rec.fieldName(nField) == "resource_id") { //make sure the fields are in order
                        QString st = rec.value(nField).toString();
                        if (type == SQLiteUtil::getTypeDescriptionSearch(ResourceType::Household)) {
                            //IF type = people
                            mapRes["HouseholderId"] = st;
                        }else
                            mapRes["Id"] = st;

                    }else if (rec.fieldName(nField) == "resource_description") {
                        QString st = rec.value(nField).toString();
                        if (type == SQLiteUtil::getTypeDescriptionSearch(ResourceType::Household)) {
                            //IF type = people
                            mapRes["Household_LastName"] = st.left(st.indexOf(","));
                            mapRes["Household_FirstName"] = st.right( (st.size() - st.indexOf(",") - 2) );
                        }else if (type == SQLiteUtil::getTypeDescriptionSearch(ResourceType::Locality) ) {
                            mapRes["Name"] = st;
                        }else if (type == SQLiteUtil::getTypeDescriptionSearch(ResourceType::Subdivision) ) {
                            mapRes["Name"] = st;
                            //mapRes["IsMainHall"] = st;
                        }
                    }else if (rec.fieldName(nField) == "resource_ad_description") {
                        QString st = rec.value(nField).toString();
                        if (type == SQLiteUtil::getTypeDescriptionSearch(ResourceType::Household)) {
                            //IF type = people
                            QVariantList childrenNames;
                            childrenNames.append(st);
                            mapRes["ChildrensFirstNames"] = childrenNames;
                        }
                    }else if (rec.fieldName(nField) == "resource_country_name") {
                        QString st = rec.value(nField).toString();
                        mapRes["CountryName"] = st;
                    }else if (rec.fieldName(nField) == "resource_locality_name") {
                        QString st = rec.value(nField).toString();
                        mapRes["LocalityName"] = st;
                    }else if (rec.fieldName(nField) == "resource_thumbnail_id") {
                        QString st = rec.value(nField).toString();

                        if (!st.isEmpty()) {

                            QMap<QString, QVariant> mapPhoto;
                            mapPhoto["SignedURL340"] = st;

                            if (type == SQLiteUtil::getTypeDescriptionSearch(ResourceType::Household)) {
                                //IF type = people
                                mapRes["HouseholdPhoto"] = mapPhoto;
                            }else
                                mapRes["HallPhoto"] = mapPhoto;
                        }
                    }

                }

                QMap<QString, QVariant> mapR;
                mapR["Type"] = type;
                mapR["Result"] = mapRes;


                listResult.append(mapR);


            }

        } else {
            const QSqlError error = query.lastError();
            qDebug() << "Get resource error: " + error.text();
        }


    }


    JsonDataAccess jda;

    QMap<QString, QVariant> map;
    map["Results"] = listResult;

    QString jsonBuffer1;
    jda.saveToBuffer(map, &jsonBuffer1);

    jsonBuffer1.replace("\r\n", "");
    jsonBuffer1.replace("''", "");
    jsonBuffer1.replace("\\", "");
    jsonBuffer1.replace("\n", "");
    jsonBuffer1.replace("\"{", "{");
    jsonBuffer1.replace("}\"", "}");


    return jsonBuffer1;
}


int CRUDResourceTable::getResourcesCount(int resType, QString resLocality, QString resSubdivision, QString resCountry)
{

    QVariantList listResult;
    QSqlDatabase database = SQLConnection();
    QString countryList = "";

    if (resType == ResourceType::CountryAll) {
        resType = ResourceType::Country;
        countryList = "\"ZZ\"";
    }

    if (resCountry.isEmpty() && resType != ResourceType::Interchange) {//There are no country info in interchn
        countryList = countryList + (countryList.isEmpty() ? "" : ",");
        countryList = countryList + AppSettings::getCurrentUserSubscribedCountries();
    }


    if (!database.tables().contains("resource")) {
        qDebug() << "Resource table does not exist.";
    } else {


        QString condition = "";
        if (resType > 0)
            condition = " WHERE resource_type = " + QString::number(resType) ;

        if (!resLocality.isEmpty())
            condition = condition +  (condition.isEmpty() ? " WHERE " : " AND ") + " resource_locality = " + resLocality;

        if (!resSubdivision.isEmpty())
            condition = condition +  (condition.isEmpty() ? " WHERE " : " AND ") + " resource_subdivision = " + resSubdivision;

        if (!resCountry.isEmpty())
            condition = condition +  (condition.isEmpty() ? " WHERE " : " AND ") + " resource_country in ( \"" + resCountry + "\" )";
        else if (!countryList.isEmpty()) {
            condition = condition +  (condition.isEmpty() ? " WHERE " : " AND ") + " resource_country in ( " + countryList + " )";
        }




        QSqlQuery query(database);
        query.prepare("SELECT count(*) as counttotal FROM resource" + condition);


        // Note that no SQL Statement is passed to 'exec' as it is a prepared statement.
        if (query.exec()) {

            while (query.next())  {

                QSqlRecord rec = query.record();
                int numFields = rec.count();
                for (int nField = 0; nField < numFields; nField++)
                {
                    if (rec.fieldName(nField) == "counttotal") {
                        return rec.value(nField).toInt();
                    }
                }

            }

        } else {
            const QSqlError error = query.lastError();
        }




    }
    return 0;
}



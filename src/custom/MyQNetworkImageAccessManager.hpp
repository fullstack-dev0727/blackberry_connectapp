/*
 * Copyright UBT Global.
 *
 *  Created on: 16 Feb 2016
 *      Author: Lucas Bento
 */


#ifndef MYQNETWORKIMAGEACCESSMANAGER_HPP_
#define MYQNETWORKIMAGEACCESSMANAGER_HPP_


#include <QNetworkAccessManager>
#include <QtCore/QObject>


class MyQNetworkImageAccessManager : public QNetworkAccessManager
{
    public:
    MyQNetworkImageAccessManager(QObject *parent=0) :QNetworkAccessManager(parent){

        };
        virtual ~MyQNetworkImageAccessManager();
        static void setupCache(MyQNetworkImageAccessManager *mMyQNetworkImageAccessManager);

    protected:
    private:
};



#endif /* MYQNETWORKIMAGEACCESSMANAGER_HPP_ */

/*
 * Copyright UBT Global.
 *
 *  Created on: 16 Feb 2016
 *      Author: Lucas Bento
 */


#ifndef MYQNETWORKACCESSMANAGER_HPP_
#define MYQNETWORKACCESSMANAGER_HPP_


#include <QNetworkAccessManager>
#include <QtCore/QObject>


class MyQNetworkAccessManager : public QNetworkAccessManager
{
    public:
        MyQNetworkAccessManager(QObject *parent=0) :QNetworkAccessManager(parent){
            setupCache();
        };
        virtual ~MyQNetworkAccessManager();
        void setupCache();

    protected:
    private:
};



#endif /* MYQNETWORKACCESSMANAGER_HPP_ */

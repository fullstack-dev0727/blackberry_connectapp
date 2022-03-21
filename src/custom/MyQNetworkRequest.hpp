/*
 * Copyright UBT Global.
 *
 *  Created on: 16 Feb 2016
 *      Author: Lucas Bento
 */


#ifndef MYQNETWORKREQUEST_HPP_
#define MYQNETWORKREQUEST_HPP_


#include <QNetworkRequest>

class MyQNetworkRequest : public QNetworkRequest
{
    public:
        MyQNetworkRequest(QString url, bool secured) :QNetworkRequest(url), secured_(secured){
            setupRequest(secured_);
        };
        MyQNetworkRequest(QNetworkRequest request) :QNetworkRequest(request){};
        virtual ~MyQNetworkRequest();
        void setupRequest(bool secured);

    protected:
    private:
        bool secured_;
};



#endif /* MYQNETWORKREQUEST_HPP_ */

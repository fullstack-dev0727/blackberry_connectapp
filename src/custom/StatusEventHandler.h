/*
 * StatusEVentHandler.h
 *
 *  Created on: Oct 30, 2016
 *      Author: petarvasilev
 */

#ifndef STATUSEVENTHANDLER_H_
#define STATUSEVENTHANDLER_H_

#include <QObject>
#include <QString>
#include <bb/AbstractBpsEventHandler>

class StatusEventHandler : public QObject, public bb::AbstractBpsEventHandler {
    Q_OBJECT
public:
    StatusEventHandler();
    virtual ~StatusEventHandler();
    virtual void event(bps_event_t *event);

signals:
    void networkStatusUpdated(bool status, QString type);
    void localeUpdated(QString language, QString country, QString locale);
};

#endif /* STATUSEVENTHANDLER_H_ */

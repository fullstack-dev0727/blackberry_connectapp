/*
 * BaseControl.h
 *
 *  Created on: Oct 30, 2016
 *      Author: petarvasilev
 */

#ifndef BASECONTROL_H_
#define BASECONTROL_H_

#include <QObject>

class BaseControl : public QObject {
    Q_OBJECT
public:
    BaseControl();
    virtual ~BaseControl();
public Q_SLOTS:
    void onTouchFunc();
};

#endif /* BASECONTROL_H_ */

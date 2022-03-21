/*
 * BaseControl.cpp
 *
 *  Created on: Oct 30, 2016
 *      Author: petarvasilev
 */
#include "BaseControl.h"

#include <bps/bps.h>
#include <bps/netstatus.h>
#include <bps/locale.h>
#include <qdebug.h>
#include "AppSettings.hpp"
#include "qdatetime.h"

BaseControl::BaseControl()
{

}

BaseControl::~BaseControl()
{

}
void BaseControl::onTouchFunc() {
    qDebug() << "touch event";
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    AppSettings::setFirstIdleTime(currentTime);
}

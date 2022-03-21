/*
 * Copyright UBT Global.
 *
 *  Created on: 16 Feb 2016
 *      Author: Lucas Bento
 */

#include "MyQNetworkImageAccessManager.hpp"
#include "../api/APIUtil.hpp"
#include "../AppSettings.hpp"
#include <QNetworkDiskCache>
#include <QDir>
#include <cstdio>

MyQNetworkImageAccessManager::~MyQNetworkImageAccessManager(){}


/*
 * Setup the access manager with the Default Caching
 * Created by Lucas Bento
 */

void MyQNetworkImageAccessManager::setupCache(MyQNetworkImageAccessManager *mMyQNetworkImageAccessManager) {

    //Cache
    QNetworkDiskCache *diskCache = new QNetworkDiskCache(mMyQNetworkImageAccessManager);
    diskCache->setCacheDirectory( QDir::homePath() + "/imagecacheDir");
    diskCache->setMaximumCacheSize(256*1024*1024); // 256MB
    mMyQNetworkImageAccessManager->setCache(diskCache);

}

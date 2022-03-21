/*
 * Copyright UBT Global.
 *
 *  Created on: 16 Feb 2016
 *      Author: Lucas Bento
 */

#include "MyQNetworkAccessManager.hpp"
#include "../api/APIUtil.hpp"
#include "../AppSettings.hpp"
#include <QNetworkDiskCache>
#include <QDir>
#include <cstdio>

MyQNetworkAccessManager::~MyQNetworkAccessManager(){}


/*
 * Setup the access manager with the Default Caching
 * Created by Lucas Bento
 */

void MyQNetworkAccessManager::setupCache() {

    //Cache
    QNetworkDiskCache *diskCache = new QNetworkDiskCache(this);
    diskCache->setCacheDirectory( QDir::homePath() + "/cacheDir");
    diskCache->setMaximumCacheSize(128*1024*1024); // 128MB
    this->setCache(diskCache);

}

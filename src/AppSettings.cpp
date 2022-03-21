/*
 * Copyright UBT Global.
 *
 *  Created on: 16 Feb 2016
 *      Author: Lucas Bento
 */


#include "AppSettings.hpp"

#include <QSettings>
#include <QString>

namespace
{
const QString organizationName = QLatin1String("UBT");
const QString applicationName = QLatin1String("Connect");
const QString pinCode = QLatin1String("pincode");
const QString firstIdle = QLatin1String("firstidle");
const QString lastOnline = QLatin1String("lastonline");
const QString tokenSetting = QLatin1String("accesstoken");
const QString refreshTokenSetting = QLatin1String("refreshtoken");
const QString countryFilterCodeSetting = QLatin1String("searchcountryfcode");
const QString countryFilterNameSetting = QLatin1String("searchcountryfname");

const QString userCountryCodeSetting = QLatin1String("countrycode");
const QString userLocalityCodeSetting = QLatin1String("localitycode");
const QString userLocalityNameSetting = QLatin1String("localityname");

const QString currentUserIdSetting = QLatin1String("currentuserid");

const QString currentUserHouseholdIdSetting = QLatin1String("currentuserhouseholdid");

const QString userEmailSetting = QLatin1String("useremail");

const QString firstAccessSetting = QLatin1String("firstaccess");

const QString firstPhotoDownload = QLatin1String("firstphotodownload");

const QString currentUserSubscribedSetting = QLatin1String("currentusersubscribed");

const QString currentUserSubscribedSettingQt = QLatin1String("currentusersubscribedqt");

const QString currentUserManageSubsLink = QLatin1String("currentusermanagesubslink");

const QString imagePageSetting = QLatin1String("imagepage");
}


int AppSettings::getImageDownloadPage()
{
    QSettings *settings = new QSettings(organizationName, applicationName);
    return settings->value(imagePageSetting, 1).toInt();
}

void AppSettings::setImageDownloadPage(int page)
{
    QSettings *settings = new QSettings(organizationName, applicationName);
    settings->setValue(imagePageSetting, QVariant(page));
    settings->sync();
}
qint64 AppSettings::getFirstIdleTime()
{
    QSettings *settings = new QSettings(organizationName, applicationName);
    return settings->value(firstIdle, 0).toLongLong();
}

void AppSettings::setFirstIdleTime(qint64 value)
{
    QSettings *settings = new QSettings(organizationName, applicationName);
    settings->setValue(firstIdle, QVariant(value));
    settings->sync();
}
qint64 AppSettings::getLastOnlineTime()
{
    QSettings *settings = new QSettings(organizationName, applicationName);
    return settings->value(lastOnline, 0).toLongLong();
}

void AppSettings::setLastOnlineTime(qint64 value)
{
    QSettings *settings = new QSettings(organizationName, applicationName);
    settings->setValue(lastOnline, QVariant(value));
    settings->sync();
}
QString AppSettings::getPinCode()
{
    QSettings *settings = new QSettings(organizationName, applicationName);
    return settings->value(pinCode, "").toString();
}

void AppSettings::setPinCode(QString value)
{
    QSettings *settings = new QSettings(organizationName, applicationName);
    settings->setValue(pinCode, QVariant(value));
    settings->sync();
}
QString AppSettings::getToken()
{
    QSettings *settings = new QSettings(organizationName, applicationName);
    return settings->value(tokenSetting, "").toString();
}

void AppSettings::setToken(QString value)
{
    QSettings *settings = new QSettings(organizationName, applicationName);
    settings->setValue(tokenSetting, QVariant(value));
    settings->sync();
}

QString AppSettings::getRefreshToken()
{
    QSettings *settings = new QSettings(organizationName, applicationName);
    return settings->value(refreshTokenSetting, "").toString();
}

void AppSettings::setRefreshToken(QString value)
{
    QSettings *settings = new QSettings(organizationName, applicationName);
        settings->setValue(refreshTokenSetting, QVariant(value));
        settings->sync();
}

QString AppSettings::getUserCountryCode()
{
    QSettings *settings = new QSettings(organizationName, applicationName);
        return settings->value(userCountryCodeSetting, "").toString();
}

void AppSettings::setUserCountryCode(QString value)
{
    QSettings *settings = new QSettings(organizationName, applicationName);
        settings->setValue(userCountryCodeSetting, QVariant(value));
        settings->sync();
}

QString AppSettings::getUserLocalityCode()
{
    QSettings *settings = new QSettings(organizationName, applicationName);
        return settings->value(userLocalityCodeSetting, "").toString();
}

void AppSettings::setUserLocalityCode(QString value)
{
    QSettings *settings = new QSettings(organizationName, applicationName);
        settings->setValue(userLocalityCodeSetting, QVariant(value));
        settings->sync();
}

QString AppSettings::getUserLocalityName()
{
    QSettings *settings = new QSettings(organizationName, applicationName);
        return settings->value(userLocalityNameSetting, "").toString();
}

void AppSettings::setUserLocalityName(QString value)
{
    QSettings *settings = new QSettings(organizationName, applicationName);
        settings->setValue(userLocalityNameSetting, QVariant(value));
        settings->sync();
}

QString AppSettings::getCountryFilterCode()
{
    QSettings *settings = new QSettings(organizationName, applicationName);
        return settings->value(countryFilterCodeSetting, "").toString();
}

void AppSettings::setCountryFilterCode(QString value)
{
    QSettings *settings = new QSettings(organizationName, applicationName);
        settings->setValue(countryFilterCodeSetting, QVariant(value));
        settings->sync();
}


QString AppSettings::getCountryFilterName()
{
    QSettings *settings = new QSettings(organizationName, applicationName);
        return settings->value(countryFilterNameSetting, "").toString();
}

void AppSettings::setCountryFilterName(QString value)
{
    QSettings *settings = new QSettings(organizationName, applicationName);
        settings->setValue(countryFilterNameSetting, QVariant(value));
        settings->sync();
}

QString AppSettings::getCurrentUserId()
{
    QSettings *settings = new QSettings(organizationName, applicationName);
        return settings->value(currentUserIdSetting, "").toString();
}

void AppSettings::setCurrentUserId(QString id)
{
    QSettings *settings = new QSettings(organizationName, applicationName);
        settings->setValue(currentUserIdSetting, QVariant(id));
        settings->sync();
}

QString AppSettings::getUserEmail()
{
    QSettings *settings = new QSettings(organizationName, applicationName);
        return settings->value(userEmailSetting, "").toString();
}

void AppSettings::setUserEmail(QString email)
{
    QSettings *settings = new QSettings(organizationName, applicationName);
        settings->setValue(userEmailSetting, QVariant(email));
        settings->sync();
}

QString AppSettings::getCurrentUserHouseholdId()
{
    QSettings *settings = new QSettings(organizationName, applicationName);
        return settings->value(currentUserHouseholdIdSetting, "").toString();
}

void AppSettings::setCurrentUserHouseholdId(QString id)
{
    QSettings *settings = new QSettings(organizationName, applicationName);
        settings->setValue(currentUserHouseholdIdSetting, QVariant(id));
        settings->sync();
}


bool AppSettings::getFirstAccess()
{
    QSettings *settings = new QSettings(organizationName, applicationName);
        return settings->value(firstAccessSetting, true).toBool();
}

void AppSettings::setFirstAccess(bool firstAccess)
{
    QSettings *settings = new QSettings(organizationName, applicationName);
        settings->setValue(firstAccessSetting, QVariant(firstAccess));
        settings->sync();
}

bool AppSettings::getFirstPhotoDownload()
{
    QSettings *settings = new QSettings(organizationName, applicationName);
        return settings->value(firstPhotoDownload, true).toBool();
}

void AppSettings::setFirstPhotoDownload(bool isFirstPhotoDownload)
{
    QSettings *settings = new QSettings(organizationName, applicationName);
        settings->setValue(firstPhotoDownload, QVariant(isFirstPhotoDownload));
        settings->sync();
}



QString AppSettings::getCurrentUserSubscribedCountries() {
    QSettings *settings = new QSettings(organizationName, applicationName);
        return settings->value(currentUserSubscribedSetting, "").toString();
}


void AppSettings::setCurrentUserSubscribedCountries(QString currentUserSubscribed) {
    QSettings *settings = new QSettings(organizationName, applicationName);
        settings->setValue(currentUserSubscribedSetting, QVariant(currentUserSubscribed));
        settings->sync();
}

int AppSettings::getCurrentUserSubscribedCountriesQt() {
    QSettings *settings = new QSettings(organizationName, applicationName);
        return settings->value(currentUserSubscribedSettingQt, "").toInt();
}


void AppSettings::setCurrentUserSubscribedCountriesQt(int currentUserSubscribedQt) {
    QSettings *settings = new QSettings(organizationName, applicationName);
        settings->setValue(currentUserSubscribedSettingQt, QVariant(currentUserSubscribedQt));
        settings->sync();
}


QString AppSettings::getCurrentUserManageSubsLink() {
    QSettings *settings = new QSettings(organizationName, applicationName);
        return settings->value(currentUserManageSubsLink, "http://www.universalbusinessteam.com/").toString();
}


void AppSettings::setCurrentUserManageSubsLink(QString link) {
    QSettings *settings = new QSettings(organizationName, applicationName);
        settings->setValue(currentUserSubscribedSetting, QVariant(currentUserManageSubsLink));
        settings->sync();

}


//bool deviceHasSufficientFileSpaceToPhotos()
//{
//    bb::FileSystemInfo fileSystemInfo;
//    qint64 dataSize = (1024 * 1024 * 1024); //1GB
//
//    QString dataFolder = QDir::currentPath();
//    qint64 freeSpace = fileSystemInfo.availableFileSystemSpace(dataFolder + "/data");
//    if (freeSpace == -1) {
//        qWarning() << "Failed to get free space - " << fileSystemInfo.errorString()
//                   << "(" << fileSystemInfo.error() << ")";
//        return(true);
//    }
//    return(freeSpace > dataSize);
//}


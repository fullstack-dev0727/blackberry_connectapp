/*
 * Copyright UBT Global.
 *
 *  Created on: 16 Feb 2016
 *      Author: Lucas Bento
 */


#ifndef APPSETTINGS_HPP
#define APPSETTINGS_HPP

class AppSettings
{
public:
    static QString getToken();
    static void setToken(QString token);

    static QString getRefreshToken();
    static void setRefreshToken(QString token);

    static QString getUserCountryCode();
    static void setUserCountryCode(QString token);

    static QString getUserLocalityCode();
    static void setUserLocalityCode(QString code);

    static QString getUserLocalityName();
    static void setUserLocalityName(QString localityName);

    static QString getCountryFilterCode();
    static void setCountryFilterCode(QString code);

    static QString getCountryFilterName();
    static void setCountryFilterName(QString name);

    static QString getCurrentUserId();
    static void setCurrentUserId(QString id);

    static QString getUserEmail();
    static void setUserEmail(QString id);

    static QString getCurrentUserHouseholdId();
    static void setCurrentUserHouseholdId(QString id);

    static bool getFirstAccess();
    static void setFirstAccess(bool firstAccess);

    static bool getFirstPhotoDownload();
    static void setFirstPhotoDownload(bool firstPhotoDownload);

    static QString getCurrentUserSubscribedCountries();
    static void setCurrentUserSubscribedCountries(QString subscribedCountries);

    static int getCurrentUserSubscribedCountriesQt();
    static void setCurrentUserSubscribedCountriesQt(int subscribedCountriesQt);

    static QString getCurrentUserManageSubsLink();
    static void setCurrentUserManageSubsLink(QString link);

    static int getImageDownloadPage();
    static void setImageDownloadPage(int page);

    static qint64 getLastOnlineTime();
    static void setLastOnlineTime(qint64 value);

    static QString getPinCode();
    static void setPinCode(QString value);

    static qint64 getFirstIdleTime();
    static void setFirstIdleTime(qint64 value);
};

#endif



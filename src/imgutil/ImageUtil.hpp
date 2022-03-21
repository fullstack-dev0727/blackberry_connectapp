/*
 * ImageUtil.hpp
 *
 *  Created on: 09/06/2016
 *      Author: Lucas
 */

#ifndef IMAGEUTIL_HPP_
#define IMAGEUTIL_HPP_



#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/OrientationSupport>
#include <bb/system/SystemDialog>
#include <QFile>
#include <QDir>
#include <QFileInfo>

#include <QDateTime>

#include <QtSql/QtSql>

#include "huaes.h"
#include "huctx.h"
#include "hugse56.h"
#include "bb/ImageData"

using namespace bb::cascades;
using namespace bb::system;

#include "GlobalContext.hpp"

class ImageUtil
{
public:
    //function
    static QString getImageFileNameFromUrl(QString url);
    static QString getImageFileNameFromUrl(QString type, QString id);
    static QString getSdcardImageFileNameFromUrl(QString url);

    void encryptFile(QString filePath, QByteArray array);
    void decryptFile(QString filePath, QByteArray hashInfo);
    QByteArray encrypt(QByteArray plainArray, QByteArray MD5);
    QByteArray decrypt(QByteArray cipherArray, QByteArray MD5);
    QByteArray getHash(QString id, QString localityId, QString countryCode);
private:
    bool crypt(bool isEncrypt, const QByteArray & in, QByteArray & out, QByteArray MD5);
    QString toHex(const QByteArray & in);
    bool fromHex(const QString in, QByteArray & toReturn);
    bool removePadding(QByteArray & out);
    void pad(QByteArray & in);
    char nibble(char c);
    void saveFile(QByteArray ba, QString filePath);

public:
    GlobalContext globalContext;
    QString _plainText,_cipherText,_recoveredPlainText;
};


#endif /* IMAGEUTIL_HPP_ */

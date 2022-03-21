/*
 * ImageUtil.cpp
 *
 *  Created on: 09/06/2016
 *      Author: Lucas
 */

#include "ImageUtil.hpp"
#include "AppSettings.hpp"
#include <bb/data/JsonDataAccess>
#include <QtCore/QFile>
#include <huaes.h>
#include <sbreturn.h>
#include <hurandom.h>
#include <bb/system/SystemToast>
#include <QtCore/QCryptographicHash>
#include "APIUtil.hpp"
#include "AESParams.hpp"
#include "AESKey.hpp"
#include "DRBG.hpp"
#include "SBError.hpp"
#include "CRUDBase.hpp"

using namespace bb::data;


QString ImageUtil::getImageFileNameFromUrl(QString url) {

    if (url.isEmpty())
        return "";

    QString fileName = url.mid(0,url.lastIndexOf("?"));
    QString id = url.mid(0,url.lastIndexOf("?"));
    fileName = fileName.split("/").last();

    if (id.split("/").length() >= 2)
        id = id.split("/").at(id.split("/").length()-2);

    //TODO - TEST FOR MORE TYPES - NOW IF ITS NOT MEMBER ITS HOUSEHOLD - HAVE TO FIX IT
    //detect type of image
    if (url.contains("_f_")) //MEMBER
        fileName = QString("%1/images/Member%2").arg(QDir::homePath(), fileName.mid(fileName.lastIndexOf("_f_")+3)) ;
    else if (url.contains("_340")) //HOUSEHOLDER
        fileName = QString("%1/images/Householder%2.jpg").arg(QDir::homePath(), id) ;
    else if (url.contains("_720")) //HOUSEHOLDER
        fileName = QString("%1/images/Householder%2_720.jpg").arg(QDir::homePath(), id) ;
    else
        fileName = QString("%1\/%2").arg(QDir::homePath(), fileName);

    return fileName;

}
QString ImageUtil::getSdcardImageFileNameFromUrl(QString url) {
    if (url.isEmpty())
            return "";

    QString fileName = url.mid(0,url.lastIndexOf("?"));
    fileName = fileName.split("/").last();
    fileName = QString("%1\/%2").arg(CONNECT_EXTERN_IMAGE_PATH, fileName);
    return fileName;
}
QString ImageUtil::getImageFileNameFromUrl(QString type, QString id) {
    if (id.isEmpty())
        return "";
    if (type.isEmpty())
        type = "Member";

    QString fileName = QString("%1/images/%2%3.jpg").arg(QDir::homePath(), type, id) ;

    return fileName;

}
bb::ImageData fromQImage(QImage &qImage) {
    bb::ImageData imageData(bb::PixelFormat::RGBA_Premultiplied, qImage.width(), qImage.height());
    unsigned char* dstLine = imageData.pixels();
    for (int y = 0; y < imageData.height(); y++) {
        unsigned char* dst = dstLine;
        for (int x = 0; x < imageData.width(); x++) {
            int srcPixel = qImage.pixel(x, y);
            *dst++ = qRed(srcPixel);
            *dst++ = qGreen(srcPixel);
            *dst++ = qBlue(srcPixel);
            *dst++ = qAlpha(srcPixel);
        }
        dstLine += imageData.bytesPerLine();
    }
    return imageData;
}
QString getFilePath(QString fileLoc)
{
    qDebug() << "fileLoc:" + fileLoc;
    QString path = "";
    QStringList list = fileLoc.split("/");
    for (int i = 0; i < list.length() - 1; i++) {
        path = path + list[i] + "/";
    }
    qDebug() << "path:" + path;
    return path;

}

QByteArray ImageUtil::encrypt(QByteArray plainArray, QByteArray MD5) {
    pad(plainArray);
    QByteArray out(plainArray.length(), 0);

    if (crypt(true, plainArray, out, MD5)) {
        return out;
    }
    return "";
}

bool ImageUtil::crypt(bool isEncrypt, const QByteArray & in,
        QByteArray & out, QByteArray MD5) {
    QByteArray key(MD5);
    QByteArray iv(MD5);
    QString fail;

//    if (!fromHex(MD5, key)) {
//        fail += "Key is not valid hex. ";
//    }
//    if (!fromHex(MD5, iv)) {
//        fail += "IV is not valid hex. ";
//    }
//
//    if (!fail.isEmpty()) {
////        toast(fail);
//        return false;
//    }

    AESParams params(globalContext);
    if (!params.isValid()) {
//        toast(
//                QString("Could not create params. %1").arg(
//                        SBError::getErrorText(params.lastError())));
        return false;
    }

    AESKey aesKey(params, key);
    if (!aesKey.isValid()) {
//        toast(
//                QString("Could not create a key. %1").arg(
//                        SBError::getErrorText(aesKey.lastError())));
        return false;
    }

    int rc;
    if (isEncrypt) {
        rc = hu_AESEncryptMsg(params.aesParams(), aesKey.aesKey(), iv.length(),
                (const unsigned char*) iv.constData(), in.length(),
                (const unsigned char *) in.constData(),
                (unsigned char *) out.data(), globalContext.ctx());
    } else {
        rc = hu_AESDecryptMsg(params.aesParams(), aesKey.aesKey(), iv.length(),
                (const unsigned char*) iv.constData(), in.length(),
                (const unsigned char *) in.constData(),
                (unsigned char *) out.data(), globalContext.ctx());
    }
    if (rc == SB_SUCCESS) {
        return true;
    }

//    toast(QString("Crypto operation failed. %1").arg(SBError::getErrorText(rc)));
    return false;

}

QByteArray ImageUtil::decrypt(QByteArray cipherArray, QByteArray MD5) {
    QByteArray out(cipherArray.length(), 0);

    if (crypt(false, cipherArray, out, MD5)) {
        if (removePadding(out)) {
            return out;
        }
    }
    return "";
}
void ImageUtil::pad(QByteArray & in) {
    int padLength = 16 - (in.length() % 16);
    for (int i = 0; i < padLength; ++i) {
        in.append((char) padLength);
    }
}
QString ImageUtil::toHex(const QByteArray & in) {
    static char hexChars[] = "0123456789abcdef";

    const char * c = in.constData();
    QString toReturn;
    for (int i = 0; i < in.length(); ++i) {
        toReturn += hexChars[(c[i] >> 4) & 0xf];
        toReturn += hexChars[(c[i]) & 0xf];
    }

    return toReturn;
}

bool ImageUtil::fromHex(const QString in, QByteArray & toReturn) {
    QString temp(in);
    temp.replace(" ","");
    temp.replace(":","");
    temp.replace(".","");
    QByteArray content(temp.toLocal8Bit());

    const char * c(content.constData());

    if (content.length() == 0 || ((content.length() % 2) != 0)) {
        return false;
    }

    for (int i = 0; i < content.length(); i += 2) {
        char a = c[i];
        char b = c[i + 1];
        a = nibble(a);
        b = nibble(b);
        if (a < 0 || b < 0) {
            toReturn.clear();
            return false;
        }
        toReturn.append((a << 4) | b);
    }
    return true;
}

bool ImageUtil::removePadding(QByteArray & out) {
    char paddingLength = out[out.length() - 1];
    if (paddingLength < 1 || paddingLength > 16) {
//        toast("Invalid padding length. Were the keys good?");
        out.clear();
        return false;
    }
    if (paddingLength > out.length()) {
//        toast("Padding is claiming to be longer than the buffer!");
        out.clear();
        return false;
    }
    for (int i = 1; i < paddingLength; ++i) {
        char next = out[out.length() - 1 - i];
        if (next != paddingLength) {
//            toast("Not all padding bytes are correct!");
            out.clear();
            return false;
        }
    }
    out.remove(out.length() - paddingLength, paddingLength);
    return true;
}
char ImageUtil::nibble(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    } else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    return -1;
}

void ImageUtil::encryptFile(QString filePath, QByteArray hashArray) {
    QFile plainFile(filePath);
    plainFile.open(QIODevice::ReadOnly);
    QByteArray plainArray = plainFile.readAll();
    plainFile.close();
    plainFile.remove();
    QByteArray cipherArray = encrypt(plainArray, hashArray);
    saveFile(cipherArray, filePath);
}
QByteArray ImageUtil::getHash(QString id, QString localityId, QString countryCode) {
    QByteArray array1 = QCryptographicHash::hash(id.toLatin1(), QCryptographicHash::Sha1);
    QByteArray array2 = QCryptographicHash::hash(array1.append(localityId), QCryptographicHash::Sha1);
    QByteArray array3 = QCryptographicHash::hash(array2.append(countryCode), QCryptographicHash::Sha1);
    QByteArray md5Array = QCryptographicHash::hash(array3.append(APIUtil::clientSecret), QCryptographicHash::Md5);
    return md5Array;
}

void ImageUtil::decryptFile(QString filePath, QByteArray hashArray) {
    QFile cipherFile(filePath);
    cipherFile.open(QIODevice::ReadOnly);
    QByteArray cipherArray = cipherFile.readAll();
    QByteArray plainArray = decrypt(cipherArray, hashArray);
    saveFile(plainArray, getFilePath(filePath) + "recovered.jpg");
}

void ImageUtil::saveFile(QByteArray ba, QString filePath) {
    // Ask the user where he/she wants to save the file
    QFile file(filePath);
    file.open(QIODevice::WriteOnly);
    // Check that the path is valid
    if (!file.fileName().isEmpty()) {
       // Write contents of ba in file
       file.write(ba);
       // Close the file
       file.close();
    }
}

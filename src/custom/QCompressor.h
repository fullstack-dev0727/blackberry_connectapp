/*
 * QCompressor.h
 *
 *  Created on: 09/06/2016
 *      Author: Lucas
 */

#ifndef QCOMPRESSOR_H_
#define QCOMPRESSOR_H_


#include <zlib.h>
#include <QByteArray>

#define GZIP_WINDOWS_BIT 15 + 16
#define GZIP_CHUNK_SIZE 32 * 1024

class QCompressor
{
public:
    static bool gzipCompress(QByteArray input, QByteArray &output, int level = -1);
    static bool gzipDecompress(QByteArray input, QByteArray &output);
};



#endif /* QCOMPRESSOR_H_ */

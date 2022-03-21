/* Copyright (c) 2012, 2013  BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "imageitem.hpp"

#include "imageprocessor.hpp"

#include <bb/ImageData>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include "../custom/MyQNetworkImageAccessManager.hpp"

/**
 *  This class implements a image loader which will initialize a network request in asynchronous manner.
 *  After receiving response from the network, it creates a QImage object in its own thread.
 *  Then it signals the interested parties about the result.
 */

/**
 *  Constructor
 */
//! [0]
ImageItem::ImageItem()
    : QObject()
{
}

ImageItem::ImageItem(const QString &imageUrl, const QVariantMap &itemData, QObject* parent)
    : QObject(parent)
    , m_loading(false)
    , m_imageUrl(imageUrl)
    , m_itemData(itemData)
{
}
//! [0]

/**
 * Destructor
 */
//! [1]
ImageItem::~ImageItem() { }
//! [1]

/**
 * ImageItem::load()
 *
 * Instruct the QNetworkAccessManager to initialize a network request in asynchronous manner.
 *
 * Also, setup the signal handler to receive the event indicating the network response.
 */
//! [2]
void ImageItem::load()
{

    QString log = "Benchmark: 10 - Request load image " + QTime::currentTime().toString("mm:ss.zzz");
    qDebug() << log;

    m_loading = true;
    emit loadingChanged();

    MyQNetworkImageAccessManager* netManager = new MyQNetworkImageAccessManager(this);


    //qDebug() << "Url : " + QUrl::fromEncoded(m_imageUrl.toLatin1());
    QUrl url =  QUrl::fromEncoded(m_imageUrl.toLatin1());

    QNetworkRequest request(url);
    //request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::AlwaysCache);

    QNetworkReply* reply = netManager->get(request);
    bool ok = connect(reply, SIGNAL(finished()), this, SLOT(onReplyFinished()));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
}
//! [2]

/**
 * ImageItem::onReplyFinished()
 *
 * Handler for the signal indicating the response for the previous network request.
 *
 * If the result was a success, it will start the thread of constructing the QImage object.
 */
//! [3]
void ImageItem::onReplyFinished()
{
    QString log = "Benchmark: 11 - Request load image response " + QTime::currentTime().toString("mm:ss.zzz");
    qDebug() << log;

    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QString response;
    if (reply) {
        qDebug() << "Error : " + reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();
        if (reply->error() == QNetworkReply::NoError) {
            const int available = reply->bytesAvailable();
            if (available > 0) {
                const QByteArray data(reply->readAll());

                // Setup the image processing thread
                ImageProcessor *imageProcessor = new ImageProcessor(data);

                QString log = "Benchmark: 12 - Request image processor " + QTime::currentTime().toString("mm:ss.zzz");
                qDebug() << log;

                QFuture<QImage> future = QtConcurrent::run(imageProcessor, &ImageProcessor::start);

                // Invoke our onProcessingFinished slot after the processing has finished.
                bool ok = connect(&m_watcher, SIGNAL(finished()), this, SLOT(onImageProcessingFinished()));
                Q_ASSERT(ok);
                Q_UNUSED(ok);

                // starts watching the given future
                m_watcher.setFuture(future);

            }
        } else {
            m_label = tr("Error: %1 status: %2").arg(reply->errorString(), reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString());
            emit labelChanged();

            m_loading = false;
            emit loadingChanged();
        }

        reply->deleteLater();
    } else {
        m_label = tr("Download failed. Check internet connection");
        emit labelChanged();

        m_loading = false;
        emit loadingChanged();
    }
}
//! [3]

/**
 * ImageItem::onImageProcessingFinished()
 *
 * Handler for the signal indicating the result of the image processing.
 */
//! [4]
void ImageItem::onImageProcessingFinished()
{
    QString log = "Benchmark: 13 - Request image processed " + QTime::currentTime().toString("mm:ss.zzz");
    qDebug() << log;

    QImage swappedImage = m_watcher.future().result().rgbSwapped();
    if(swappedImage.format() != QImage::Format_RGB32) {
    	swappedImage = swappedImage.convertToFormat(QImage::Format_RGB32);
    }
    const bb::ImageData imageData = bb::ImageData::fromPixels(swappedImage.bits(), bb::PixelFormat::RGBX, swappedImage.width(), swappedImage.height(), swappedImage.bytesPerLine());

    m_image = bb::cascades::Image(imageData);
    emit imageChanged();

    m_label.clear();
    emit labelChanged();

    m_loading = false;
    emit loadingChanged();

    log = "Benchmark: 14 - Request image converted " + QTime::currentTime().toString("mm:ss.zzz");
    qDebug() << log;
}
//! [4]

QVariant ImageItem::image() const
{
    return QVariant::fromValue(m_image);
}

QVariantMap ImageItem::itemData() const
{
    return m_itemData;
}

QString ImageItem::label() const
{
    return m_label;
}

bool ImageItem::loading() const
{
    return m_loading;
}



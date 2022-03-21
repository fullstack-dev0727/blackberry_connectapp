#include "ImageDownloader.hpp"

#include <QNetworkRequest>
#include <QNetworkReply>

using namespace bb::cascades;

ImageDownloader::ImageDownloader(QObject* parent):
    QObject(parent), mIsValid(false) {}

ImageDownloader::~ImageDownloader() {}

QString ImageDownloader::url() const {
    return mImageUrl;
}

void ImageDownloader::setUrl( const QString& url)
{
    if(url != mImageUrl) {
        mImageUrl = url;
        mIsValid = false;
        mImage = bb::cascades::Image();
        emit urlChanged();
        emit imageChanged();
        startDownload();
    }
}

QVariant ImageDownloader::image() const {
    return QVariant::fromValue(mImage);
}

bool ImageDownloader::isValid() const {
    return mIsValid;
}

void ImageDownloader::startDownload() {
    MyQNetworkImageAccessManager::setupCache(&mNetManager);

    QNetworkRequest request(mImageUrl);
    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::AlwaysCache);

    QSslConfiguration config = request.sslConfiguration();
                config.setPeerVerifyMode(QSslSocket::VerifyNone);
                config.setProtocol(QSsl::TlsV1SslV3);
    request.setSslConfiguration(config);

    QNetworkReply* reply = mNetManager.get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(onReplyFinished()));
}

void ImageDownloader::onReplyFinished() {
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QString response;
    if (reply) {
        if (reply->error() == QNetworkReply::NoError) {
            const int available = reply->bytesAvailable();
            if (available > 0) {
                const QByteArray data(reply->readAll());


                //process Image
                QImage image;
                image.loadFromData(data);
                image = image.scaled(500, 500, Qt::KeepAspectRatio);
                //convert
                if(image.format() != QImage::Format_RGB32) {
                    image = image.convertToFormat(QImage::Format_RGB32);
                }
                image = image.rgbSwapped();
                const bb::ImageData imageData = bb::ImageData::fromPixels(image.bits(), bb::PixelFormat::RGBX, image.width(), image.height(), image.bytesPerLine());

                //Define image
                mImage = bb::cascades::Image(imageData);

                mIsValid = true;
                emit imageChanged();
            }
        }
        reply->deleteLater();
    }
}



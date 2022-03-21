#ifndef IMAGEDOWNLOADER_HPP_
#define IMAGEDOWNLOADER_HPP_


#include <QtCore/QObject>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <bb/data/JsonDataAccess>
#include <bb/cascades/Image>

#include "../custom/MyQNetworkImageAccessManager.hpp"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <bb/ImageData>
#include <bb/PixelFormat>
#include <QtGui/QImage>
#include <QDebug>



using namespace bb::cascades;

class QNetworkAccessManager;

class ImageDownloader: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant image READ image NOTIFY imageChanged)
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(bool isVaid READ isValid CONSTANT);
public:
    ImageDownloader( QObject* parent = 0);
    virtual ~ImageDownloader();

signals:
    void urlChanged();
    void imageChanged();

private slots:
    QString url() const;
    void setUrl( const QString& url);

    QVariant image() const;
    bool isValid() const;

    void startDownload();
    void onReplyFinished();

private:
    MyQNetworkImageAccessManager mNetManager;
    QString mImageUrl;
    bb::cascades::Image mImage;
    bool mIsValid;
};

#endif /* IMAGEDOWNLOADER_HPP_ */

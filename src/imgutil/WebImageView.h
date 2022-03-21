#ifndef WEBIMAGEVIEW_H_
#define WEBIMAGEVIEW_H_

// Sets to -1 to disabled deleting cached images
#define MAX_NUMBER_OF_IMAGES_SAVED 50000

#include <bb/cascades/ImageView>
#include <QNetworkAccessManager>
#include <QNetworkDiskCache>
#include <bb/device/CellularNetworkInfo>
#include <bb/device/CellularRadioInfo>
#include "ImageUtil.hpp"
#include "../api/APIUtil.hpp"

#include "../custom/MyQNetworkRequest.hpp"
#include "../custom/MyQNetworkAccessManager.hpp"


#include <QUrl>

using namespace bb::cascades;
using namespace bb::device;

class WebImageView: public bb::cascades::ImageView {
    Q_OBJECT
    Q_PROPERTY (QVariantMap postLoadingUrl READ postLoadingUrl WRITE setPostLoadingUrl NOTIFY postLoadingUrlChanged)
    Q_PROPERTY (QVariantMap url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY (float loading READ loading NOTIFY loadingChanged)

public:
    WebImageView();
    virtual ~WebImageView() {}
    const QVariantMap& url() const;
    const QVariantMap& postLoadingUrl() const;
    double loading() const;
    ImageUtil imageUtil;

    void loadImage(QUrl url, bool reset, bool forceUpdate);
    Q_INVOKABLE void clearCache();

public Q_SLOTS:
    void setUrl(QVariantMap url);
    void setPostLoadingUrl(QVariantMap url);

private Q_SLOTS:
    void imageLoaded();
    void dowloadProgressed(qint64,qint64);

private:
    static MyQNetworkAccessManager * mNetManager;
    static QNetworkDiskCache * mNetworkDiskCache;
    static CellularRadioInfo *cellularRadioInfo;
    static CellularNetworkInfo *cellularNetworkInfo;

    QVariantMap mUrl;
    QVariantMap mPostLoadingUrl;
    float mLoading;
    bool mPostLoadingUrlLoaded;

    bool isARedirectedUrl(QNetworkReply *reply);
    void setURLToRedirectedUrl(QNetworkReply *reply);
    bool loadFromFile(QString filePath);
    void releaseSomeCache(const int& maxNumberOfImagesSaved);
    void loadImageFromUrl(QString url);
signals:
    void urlChanged();
    void postLoadingUrlChanged();
    void loadingChanged();
};

#endif /* WEBIMAGEVIEW_H_ */

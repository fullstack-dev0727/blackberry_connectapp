/*
 * DownloadManagerControl.hpp
 *
 *  Created on: 19/07/2016
 *      Author: Lucas
 */

#include "DownloadManager.hpp"

#include <QtCore/QFileInfo>
#include <QtCore/QTimer>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

#include <QtCore/QFile>
#include <bb/Application>
#include <bb/data/JsonDataAccess>
#include <QCoreApplication>
#include <QTextCodec>
#include <QtCore/QTime>
#include <qdir.h>
#include "../custom/MyQNetworkRequest.hpp"

DownloadManager::DownloadManager(QObject *parent) :
        QObject(parent), m_currentDownload(0), m_downloadedCount(0), m_totalCount(0), m_progressTotal(
                0), m_progressValue(0), requestRetry(false), m_database(false), pagesTotal(1), pagesDownloaded(
                1) //, mSheet(0)
{
}

QString DownloadManager::errorMessage() const
{
    return m_errorMessage.join("\n");
}

bool DownloadManager::database() const
{
    return m_database;
}

QString DownloadManager::statusMessage() const
{
    return m_statusMessage.join("\n");
}

int DownloadManager::activeDownloads() const
{
    return m_downloadQueue.count();
}

int DownloadManager::progressTotal() const
{
    return m_progressTotal;
}

int DownloadManager::progressValue() const
{
    return m_progressValue;
}

QString DownloadManager::progressMessage() const
{
    return m_progressMessage;
}

void DownloadManager::downloadUrl(const QString &url)
{
    qDebug() << "url:" + url;
    append(QUrl(url));
}

void DownloadManager::append(const QUrl &url)
{
    /**
     * If there is no job in the queue at the moment or we do
     * not process any job currently, then we trigger the processing
     * of the next job.
     */
    if (m_downloadQueue.isEmpty() && !m_currentDownload)
        QTimer::singleShot(0, this, SLOT(startNextDownload()));

    // Enqueue the new URL to the job queue
    m_downloadQueue.enqueue(url);

    emit activeDownloadsChanged();

    // Increment the total number of jobs
    ++m_totalCount;
}

QString DownloadManager::saveFileName(const QUrl &url)
{
    // First extract the path component from the URL ...
    //const QString path = url.path();

    // ... and then extract the file name.
    //QString basename = QFileInfo(path).fileName();
    QString basename = ImageUtil::getImageFileNameFromUrl(url.toString());

    if (basename.isEmpty())
        basename = "data/download";

    //    /**
    //     * Check if the file name exists already, if so, append an increasing number and test again.
    //     */
    //    if (QFile::exists(basename)) {
    //        // already exists, don't overwrite
    //        int i = 0;
    //        basename += '.';
    //        while (QFile::exists(basename + QString::number(i)))
    //            ++i;
    //
    //        basename += QString::number(i);
    //    }

    return basename;
}

void DownloadManager::addErrorMessage(const QString &message)
{
    m_errorMessage.append(message);
    emit errorMessageChanged();
}

void DownloadManager::addStatusMessage(const QString &message)
{
    m_statusMessage.append(message);
    emit statusMessageChanged();
}

void DownloadManager::startStatus()
{
    // Update the properties with the new progress values
    m_progressTotal = pagesTotal;
    m_progressValue = pagesDownloaded;
    emit progressTotalChanged();
    emit progressValueChanged();
    // ... and update the progress message.
    m_progressMessage = QString("Page %1 of %2").arg(QString::number(pagesDownloaded),
            QString::number(pagesTotal));
    emit progressMessageChanged();
}
void DownloadManager::startNextDownload()
{
    // If the queue is empty just add a new status message
    if (m_downloadQueue.isEmpty()) {
        if (!m_database) { //if it's not the database, it's downloading the images
            emit databaseChanged();
            pagesDownloaded++;
            // Update the properties with the new progress values
            m_progressValue = pagesDownloaded;
            emit progressValueChanged();
            // ... and update the progress message.
            m_progressMessage = QString("Page %1 of %2").arg(QString::number(pagesDownloaded),
                    QString::number(pagesTotal));
            emit progressMessageChanged();
            addStatusMessage(
                    QString("%1 files downloaded successfully.. Waiting for next page.").arg(
                            QString::number(m_downloadedCount)));
        } else
            addStatusMessage(
                    QString("%1 of %2 files downloaded successfully..").arg(
                            QString::number(m_downloadedCount), QString::number(m_totalCount)));

        emit sdownloadingDone(!m_database);
        return;
    }

    // Otherwise dequeue the first job from the queue ...
    const QUrl url = m_downloadQueue.dequeue();

    // ... and determine a local file name where the result can be stored.
    QString filename = "";

    // Open the file with this file name for writing
    if (!(url.toString().contains("api"))) { //When calling the API it will get a redirect - don't need to save the return
        filename = saveFileName(url);
        m_output.setFileName(filename);
        if (QDir().exists(getFilePath(filename))) {
            qDebug() << "exists before open true path:" + getFilePath(filename);
            qDebug() << "exists before open true:" + filename;
        } else {
            QDir().mkdir(getFilePath(filename));
            qDebug() << "exists before open FALSE path:" + getFilePath(filename);
            qDebug() << "exists before open FALSE:" + filename;
        }
        if (!m_output.open(QIODevice::WriteOnly)) {
            addErrorMessage(
                    QString("Problem opening save file '%1' for download '%2': %3").arg(filename,
                            url.toString(), m_output.errorString()));

            startNextDownload();
            return; // skip this download
        }
    }

    // Now create the network request for the URL ...
    MyQNetworkRequest request(url.toString(), true);

    // ... and start the download.
    m_currentDownload = m_manager.get(request);

    // Connect against the necessary signals to get informed about progress and status changes
    if (m_database)
        connect(m_currentDownload, SIGNAL(downloadProgress(qint64, qint64)),
                SLOT(downloadProgress(qint64, qint64)));

    connect(m_currentDownload, SIGNAL(finished()), SLOT(downloadFinished()));

    if (!(url.toString().contains("api")))
        connect(m_currentDownload, SIGNAL(readyRead()), SLOT(downloadReadyRead()));

    // Add a status message
    //addStatusMessage(QString("Downloading %1...").arg(url.toString()));

    //addStatusMessage(QString("Downloading Photo File..."));

    if (m_downloadQueue.size() == 0)
        addStatusMessage(QString("Extracting zip file. This can take up to 20min..."));

    // Start the timer so that we can calculate the download speed later on
    m_downloadTime.start();
}

void DownloadManager::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    // Update the properties with the new progress values
    m_progressTotal = bytesTotal;
    m_progressValue = bytesReceived;
    emit progressTotalChanged();
    emit progressValueChanged();

    // Calculate the download speed ...
    double speed = bytesReceived * 1000.0 / m_downloadTime.elapsed();
    QString unit;
    if (speed < 1024) {
        unit = "bytes/sec";
    } else if (speed < 1024 * 1024) {
        speed /= 1024;
        unit = "kB/s";
    } else {
        speed /= 1024 * 1024;
        unit = "MB/s";
    }

    // ... and update the progress message.
    m_progressMessage = QString("%1 %2").arg(speed, 3, 'f', 1).arg(unit);
    emit progressMessageChanged();
}

void DownloadManager::downloadFinished()
{
    // Reset the progress information when the download has finished
    if (m_database) {
        m_progressTotal = 0;
        m_progressValue = 0;
        m_progressMessage.clear();
        emit progressValueChanged();
        emit progressTotalChanged();
        emit progressMessageChanged();
    }

    // Close the file where the data have been written
    m_output.close();

    const QVariant redirectionTarget = m_currentDownload->attribute(
            QNetworkRequest::RedirectionTargetAttribute);

    // Add a status or

    if (m_currentDownload->error()) {

        if (m_currentDownload->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 401) { //401 Unauthorized
            if (!requestRetry) {

                requestRetry = true;

                //Try to refresh token
                if (APIUtil::refreshToken()) {

                    //tries again
                    QUrl url = m_currentDownload->url();
                    m_downloadQueue.append(url);

                    requestRetry = false;
                }
            } else {

                //failed
                //TODO - SHow error message
                emit sdownloadingDone(false);
                return;
            }
        } else {
            QString msg = m_currentDownload->errorString();
            addErrorMessage(QString("Failed: %1").arg(msg));
        }

        //        //Try again
        //        addStatusMessage("Trying again.");
        //        QUrl url = m_currentDownload->url();
        //        m_downloadQueue.append(url);
    } else if (!redirectionTarget.isNull()) {
        // If we got a redirect response (3XX), retrieve the redirect URL ...
        const QUrl newUrl = m_currentDownload->url().resolved(redirectionTarget.toUrl());

        // ... and trigger a new download request with the new URL.
        downloadUrl(newUrl.toString());

    } else {
        //addStatusMessage("Succeeded.");
        ++m_downloadedCount;
    }
    /**
     * We can't call 'delete m_currentDownload' here, because this method might have been invoked directly as result of a signal
     * emission of the network reply object.
     */
    m_currentDownload->deleteLater();
    m_currentDownload = 0;
    emit activeDownloadsChanged();

    // Trigger the execution of the next job
    startNextDownload();
}

QString DownloadManager::getFilePath(QString fileLoc)
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

void DownloadManager::downloadReadyRead()
{
    if (QDir().exists(getFilePath(m_output.fileName()))) {
        qDebug() << "exists true path:" + getFilePath(m_output.fileName());
        qDebug() << "exists true :" + m_output.fileName();
    } else {
        QDir().mkdir(getFilePath(m_output.fileName()));
        qDebug() << "exists FALSE path:" + getFilePath(m_output.fileName());
        qDebug() << "exists FALSE:" + m_output.fileName();
    }
    // Whenever new data are available on the network reply, write them out to the result file
    m_output.write(m_currentDownload->readAll());
}

//void DownloadManager::cancel()
//{
//    close();
//}
//
//void DownloadManager::close()
//{
//    //mSheet->close();
//}
//
//
//void DownloadManager::setHomeSource(AbstractPane *root)
//{
//    homeSource = root;
//}
//
//void DownloadManager::setRoot(Page *root)
//{
//    rootSource = root;
//
//}

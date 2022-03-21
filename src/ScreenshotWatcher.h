#ifndef SCREENSHOTWATCHER_H
#define SCREENSHOTWATCHER_H

#include <QDebug>
#include <QObject>
#include <QMessageBox>
#include <Qt/qdeclarativedebug.h>
#include "ScreenshotWatcher.h"
#include <QFileSystemWatcher>
#include <QUrl>
#include <QtCore/QDir>
#include <QtCore/QStringList>
#include <unistd.h>

class ScreenshotWatcher : public QObject
{
    Q_OBJECT

public:
    ScreenshotWatcher(QObject* parent=0)
    :QObject(parent){}

    ~ScreenshotWatcher(){}

    QFileSystemWatcher watcher;
    QStringList files;

    public slots:


    void onFullscreen() {
        qDebug() << "Fullscreen";


        QDir cameraFolder;
        cameraFolder.setPath("/accounts/1000/shared/camera/");
        files = cameraFolder.entryList(QDir::Files, QDir::Time);

        watcher.addPath(QUrl("/accounts/1000/shared/camera/").toString());
        QObject::connect(&watcher, SIGNAL(directoryChanged(QString)), this, SLOT(showModified(QString)));

    }

    void onInvisible() {
        qDebug() << "Invisible";
        watcher.removePath(QUrl("/accounts/1000/shared/camera/").toString());
    }

    void showModified(const QString& str)
    {
        qDebug() << "Modified";
        watcher.removePath(QUrl("/accounts/1000/shared/camera/").toString());

        QDir cameraFolder;
        cameraFolder.setPath("/accounts/1000/shared/camera/");
        QStringList newFiles = cameraFolder.entryList(QDir::Files, QDir::Time);

        if (newFiles.size() > files.size()) {
            QString filename = newFiles.at(0).toAscii(); //just last modified

            if (filename.contains("IMG")) {
                qDebug() << "Something has been added to the camera folder. Going to remove :D  File: " + filename;

                QString fileToRemove = QString("/accounts/1000/shared/camera/%2").arg(filename);
                QFile::remove(fileToRemove);
                qDebug() << fileToRemove;
            }
        }

        //Wait for a second
        watcher.addPath(QUrl("/accounts/1000/shared/camera/").toString());

    }
};

#endif // SCREENSHOTWATCHER_H

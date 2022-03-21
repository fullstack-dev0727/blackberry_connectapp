/*
 * Copyright UBT Global.
 *
 *  Created on: 16 Feb 2016
 *      Author: Lucas Bento
 */


#include "AppUi.hpp"
#include "control/HomeControl.hpp"
#include "api/APILoginRequest.hpp"
#include "imgutil/ImageDownloader.hpp"
#include "imgutil/WebImageView.h"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>




using namespace bb::cascades;

AppUi::AppUi() :
        QObject()
{
    // prepare the localization
    m_pTranslator = new QTranslator(this);
    m_pLocaleHandler = new LocaleHandler(this);

    bool res = QObject::connect(m_pLocaleHandler, SIGNAL(systemLanguageChanged()), this, SLOT(onSystemLanguageChanged()));
    // This is only available in Debug builds
    Q_ASSERT(res);
    // Since the variable is not used in the app, this is added to avoid a
    // compiler warning
    Q_UNUSED(res);

    // initial load
    onSystemLanguageChanged();

    //Register Types
    qmlRegisterType<ImageDownloader>("my.library",1, 0, "ImageDownloader");
    qmlRegisterType<WebImageView>("my.library", 1, 0, "WebImageView");

    // Create scene document from main.qml asset, the parent is set
    // to ensure the document gets destroyed properly at shut down.
    QmlDocument *qml = QmlDocument::create("asset:///HomeScreen.qml").parent(this);

    //Expose LoginControl to qml
    HomeControl *homeControl = new HomeControl(this);
    qml->setContextProperty("_control", homeControl);

    // Create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();
    homeControl->setRoot(root);

    // Set created root object as the application scene
    Application::instance()->setScene(root);

    //check sync
    //homeControl->checkSync();

}

void AppUi::onSystemLanguageChanged()
{
    QCoreApplication::instance()->removeTranslator(m_pTranslator);
    // Initiate, load and install the application translation files.
    QString locale_string = QLocale().name();
    QString file_name = QString("ConnectApp_%1").arg(locale_string);
    if (m_pTranslator->load(file_name, "app/native/qm")) {
        QCoreApplication::instance()->installTranslator(m_pTranslator);
    }
}



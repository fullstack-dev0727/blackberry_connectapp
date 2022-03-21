/*
 * Copyright (c) 2011-2015 BlackBerry Limited.
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

#include "AppUi.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/Window>

#include <QLocale>
#include <QTranslator>

#include <Qt/qdeclarativedebug.h>
#include "ScreenshotWatcher.h"

using namespace bb::cascades;

void myMessageOutput(QtMsgType type, const char* msg) {
    fprintf(stdout, "%s\n", msg);
    fflush(stdout);
}

Q_DECL_EXPORT int main(int argc, char **argv)
{
    Application app(argc, argv);
    qInstallMsgHandler(myMessageOutput);

    Window *winId = Application::instance()->mainWindow();
    Application::instance()->mainWindow()->setScreenIdleMode(ScreenIdleMode::Normal);
    if( winId != NULL )
    {
        int idleMode = SCREEN_IDLE_MODE_NORMAL;
        screen_set_window_property_iv( screen_window_t(winId), SCREEN_PROPERTY_IDLE_MODE, &idleMode);
    }


    // Create the Application UI object, this is where the main.qml file
    // is loaded and the application scene is set.
    AppUi appui;



    //Screenshot blocking
    ScreenshotWatcher* mc = new ScreenshotWatcher;

    QObject::connect(&app, SIGNAL( fullscreen() ), mc, SLOT( onFullscreen() ));
    QObject::connect(&app, SIGNAL( invisible() ), mc, SLOT( onInvisible() ));

    // Enter the application main event loop.
    return Application::exec();
}

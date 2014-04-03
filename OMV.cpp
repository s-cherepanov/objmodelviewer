/*******************************************************************************************
**
** Project: Obj Model Viewer
** File: OMV.cpp
**
** Copyright (C) 2011 Marcin Piotrowski.
** All rights reserved.
** Contact: Techvoid (contact@techvoid.net)
**
** This program is free software: you can redistribute it and/or modify it under the terms
** of the GNU General Public License as published by the Free Software Foundation, either
** version 3 of the License, or (at your option) any later version.
**
** This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
** without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License along with this
** program. If not, see <http://www.gnu.org/licenses/>.
**
*******************************************************************************************/

/*======================================== HEADERS =======================================*/

#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>

#include <QtCore/QFileInfo>

#include <windows.h>

#include "window.h"
#include "console.h"

/*======================================== GLOBAL ========================================*/

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QStringList arguments = app.arguments();
    arguments.takeFirst();

    Window win;
    win.resize(win.sizeHint());

    foreach(QString argument, arguments) {
        QFileInfo file(argument);
        if (file.isFile())
            win.openFile(file.fileName());

        if (argument == "debug")
            Console con;
    }

    int desktopArea = QApplication::desktop()->width() *
                      QApplication::desktop()->height();
    int widgetArea = win.width() * win.height();
    if (((float)widgetArea / (float)desktopArea) < 0.75f)
        win.show();
    else
        win.showMaximized();

    return app.exec();
}

/*========================================================================================*/

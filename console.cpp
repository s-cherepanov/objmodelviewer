/*******************************************************************************************
**
** Project: Obj Model Viewer
** File: console.cpp
**
** Copyright (C) 2012 Marcin Piotrowski.
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

#include "console.h"

#include <QtCore/QByteArray>

#include <iostream>
#include <cstdio>
#include <windows.h>

#include "global.h"

/*======================================== PUBLIC ========================================*/

Console::Console()
{
    alloc();
}

Console::~Console()
{

}

void Console::alloc()
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "r", stdin);
    std::ios::sync_with_stdio();
    printf("=================================================\n");
    printf("               OMV debug console                 \n");
    printf("                 version " + QByteArray(APP_FILEVER) + "\n");
    printf("=================================================\n");
}

/*======================================= PROTECTED ======================================*/

/*======================================== PRIVATE =======================================*/

/*========================================================================================*/

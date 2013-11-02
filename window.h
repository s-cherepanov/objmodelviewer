/*******************************************************************************************
**
** Project: Obj Model Viewer
** File: window.h
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

#ifndef WINDOW_H
#define WINDOW_H

#include <qtGui/QtGui>
#include <QtGui/QMainWindow>

#include "Generated/window_ui.h"

/*======================================== CLASSES =======================================*/

class QSlider;
class GLWidget;

class Window : public QMainWindow
{
	Q_OBJECT

public:
	Window(QWidget *parent = 0);

public slots:
    bool openFile(const QString &Path = QString());

private slots:
	void IsSliders();
	void IsSmooth();
	void IsWireframe();
	void IsStats();
	void PickColor();
	void SetSliders(bool value);
	void About();

protected:
	void keyPressEvent(QKeyEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event);

private:
	Ui_windowClass MainWindow;

	QString fileName;
	QAction *openAct;
	QAction *OptionsAct;
	QAction *AboutAct;
	QAction *exitAct;

	QSlider *createSlider();
	QSlider *createZoomSlider();

	GLWidget *glWidget;
	QSlider  *xSlider;
	QSlider  *ySlider;
	QSlider  *zSlider;
	QSlider  *disSlider;
};

#endif // WINDOW_H

/*========================================================================================*/

/*******************************************************************************************
**
** Project: Obj Model Viewer
** File: window.cpp
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

#include "window.h"

#include <QtCore/QUrl>
#include <QtCore/QMimeData>

#include <QtGui/QHBoxLayout>
#include <QtGui/QFileDialog>
#include <QtGui/QKeyEvent>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QColorDialog>
#include <QtGui/QMessageBox>

#include <windows.h>

#include "glwidget.h"
#include "global.h"

/*======================================== PUBLIC ========================================*/

Window::Window(QWidget *parent) :
    QMainWindow(parent)
{
	MainWindow.setupUi(this);
	setAcceptDrops(true);

	glWidget = new GLWidget(this);
	xSlider = createSlider();
	ySlider = createSlider();
	zSlider = createSlider();
	disSlider = createZoomSlider();

	//x,y,z rotation sliders
	connect(xSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setXRotation(int)));
	connect(glWidget, SIGNAL(xRotationChanged(int)), xSlider, SLOT(setValue(int)));
	connect(ySlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setYRotation(int)));
	connect(glWidget, SIGNAL(yRotationChanged(int)), ySlider, SLOT(setValue(int)));
	connect(zSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setZRotation(int)));
	connect(glWidget, SIGNAL(zRotationChanged(int)), zSlider, SLOT(setValue(int)));

	//distance slider
	connect(disSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setDistance(int)));
	connect(glWidget, SIGNAL(distanceChanged(int)), disSlider, SLOT(setValue(int)));

	//buttons - file
	connect(MainWindow.actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
	connect(MainWindow.actionAbout, SIGNAL(triggered()), this, SLOT(About()));
	connect(MainWindow.actionExit, SIGNAL(triggered()), this, SLOT(close()));

	//buttons - options
	connect(MainWindow.actionSliders, SIGNAL(triggered()), this, SLOT(IsSliders()));
	connect(MainWindow.actionSmooth, SIGNAL(triggered()), this, SLOT(IsSmooth()));
	connect(MainWindow.actionStatistics, SIGNAL(triggered()), this, SLOT(IsStats()));
	connect(MainWindow.actionWireframe, SIGNAL(triggered()), this, SLOT(IsWireframe()));
	connect(MainWindow.actionBg_color, SIGNAL(triggered()), this, SLOT(PickColor()));

	QHBoxLayout *mainLayout = new QHBoxLayout(this);
	mainLayout->addWidget(glWidget);
	mainLayout->addWidget(xSlider);
	mainLayout->addWidget(ySlider);
	mainLayout->addWidget(zSlider);
	mainLayout->addWidget(disSlider);
	MainWindow.centralWidget->setLayout(mainLayout);

	xSlider->setValue(0 * 16);
	ySlider->setValue(0 * 16);
	zSlider->setValue(0 * 16);
	disSlider->setValue(-1);
}

/*===================================== PUBLIC SLOTS =====================================*/

bool Window::openFile(const QString &Path)
{
    if(Path.isNull())
        fileName = QFileDialog::getOpenFileName(this,"Choose a file to open",
                                    NULL, "wavefront format (*.obj)");
    else fileName = Path;

	if(!fileName.isEmpty()){
        glWidget->readFromFile(fileName.toUtf8().data());
		setWindowTitle("Obj Model Viewer ( " + fileName + " )");
		return true;
	}
    return false;
}

/*===================================== PRIVATE SLOTS ====================================*/

void Window::PickColor()
{
	glWidget->bgColor = QColorDialog::getColor();
}

void Window::SetSliders(bool value)
{
	xSlider->setShown(value);
	ySlider->setShown(value);
	zSlider->setShown(value);
	disSlider->setShown(value);
}

void Window::IsSliders()
{
    SetSliders(MainWindow.actionSliders->isChecked());
}

void Window::IsStats()
{
    glWidget->SetStats(MainWindow.actionStatistics->isChecked());
}

void Window::IsWireframe()
{
    glWidget->SetWireframe(MainWindow.actionWireframe->isChecked());
}

void Window::IsSmooth()
{
    glWidget->setSmooth(MainWindow.actionSmooth->isChecked());
}

void Window::About()
{
    QMessageBox::about(this, "About Obj Model Viewer",
                       "<b>Obj Model Viewer, version " + QString(APP_FILEVER) + "</b><br>" \
                       "author: <a href=\"mailto:contact@techvoid.net\">Techvoid</a> " \
                       "(<a href=\"http://techvoid.net\">website</a>)<br><br>" \
                       "For more information check the readme file.");
}

/*======================================= PROTECTED ======================================*/

void Window::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape)
		close();
	else
		QWidget::keyPressEvent(event);
}

void Window::dragEnterEvent(QDragEnterEvent *event)
{

    const QMimeData *MimeData = event->mimeData();
    if (MimeData->hasUrls()){
        QList<QUrl> UrlList = MimeData->urls();
        foreach(QUrl Url, UrlList){
            QFileInfo File(Url.toLocalFile());
            if(File.suffix() == "obj"){
                event->acceptProposedAction();
            }
        }
    }
}

void Window::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void Window::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
}

void Window::dropEvent(QDropEvent *event)
{
    const QMimeData *MimeData = event->mimeData();
    if (MimeData->hasUrls()){
        QList<QUrl> UrlList = MimeData->urls();
        foreach(QUrl Url, UrlList){
            QString File = Url.toLocalFile();
            if(openFile(File))
                event->acceptProposedAction();
        }
    }
}

/*======================================== PRIVATE =======================================*/

QSlider *Window::createSlider()
{
	QSlider *slider = new QSlider(Qt::Vertical);
	slider->setRange(0, 360 * 16);
	slider->setSingleStep(16);
	slider->setPageStep(15 * 16);
	slider->setTickInterval(15 * 16);
	slider->setTickPosition(QSlider::TicksRight);
	return slider;
}

QSlider *Window::createZoomSlider()
{
	QSlider *slider = new QSlider(Qt::Vertical);
	slider->setRange(-12, 12);
	slider->setSingleStep(1);
	slider->setPageStep(1);
	slider->setTickInterval(1);
	slider->setTickPosition(QSlider::TicksRight);
	return slider;
}

/*========================================================================================*/

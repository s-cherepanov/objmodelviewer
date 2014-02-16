/*******************************************************************************************
**
** Project: Obj Model Viewer
** File: glwidget.cpp
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

#include "glwidget.h"

#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>

#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/glut.h>

#include "glm.h"

/*======================================== PUBLIC ========================================*/

bool	 wireframe = false;
bool	 stats	   = true;
bool	 smooth    = true;
char	 *model	   = NULL;
GLMmodel *pmodel1  = NULL;

int		FPS = 0, Frames = 0;
DWORD	LastFPS = 0;

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
	xRot = 0;
	yRot = 0;
	zRot = 0;

	bgColor = QColor::fromRgb(0,0,0,0);
}

QSize GLWidget::minimumSizeHint() const
{
	return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
	return QSize(400, 400);
}

void GLWidget::readFromFile(char *file)
{
	if(file != model) {
		model = file;
        pmodel1 = glmReadOBJ(model);
        glmUnitize(pmodel1);
        glmFacetNormals(pmodel1);
        printf("model loaded \"%s\"\n", model);
	}
	updateGL();
}

static void qNormalizeAngle(int &angle)
{
	while (angle < 0)
		angle += 360 * 16;
	while (angle > 360 * 16)
		angle -= 360 * 16;
}

/*===================================== PUBLIC SLOTS =====================================*/

void GLWidget::SetWireframe(bool value)
{
    wireframe = value;
	updateGL();
}

void GLWidget::setSmooth(bool value)
{
    smooth = value;
	updateGL();
}

void GLWidget::SetStats(bool value)
{
    stats = value;
	updateGL();
}

void GLWidget::setXRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != xRot) {
		xRot = angle;
		emit xRotationChanged(angle);
		updateGL();
	}
}

void GLWidget::setYRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != yRot) {
		yRot = angle;
		emit yRotationChanged(angle);
		updateGL();
	}
}

void GLWidget::setZRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != zRot) {
		zRot = angle;
		emit zRotationChanged(angle);
		updateGL();
	}
}

void GLWidget::setDistance(int dis)
{
	if(dis != disPos){
		disPos = dis;
		emit distanceChanged(dis);
	}
	updateGL();
}

/*===================================== PRIVATE SLOTS ====================================*/

/*======================================= PROTECTED ======================================*/

void GLWidget::initializeGL()
{
	qglClearColor(bgColor);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);

	static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void GLWidget::paintGL()
{
	qglClearColor(bgColor);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// fps
	if( GetTickCount() - LastFPS >= 1000 )
	{
		LastFPS = GetTickCount();
		FPS = Frames;
		Frames = 0;
	}
	Frames++;

	glTranslatef(0.0, 0.0, -10.0);
	glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
	glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
	glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
	updateView();

	if(wireframe){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(1);
        glDisable(GL_LIGHTING);
        glDisable(GL_CULL_FACE);
	} else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_LIGHTING);
        glEnable(GL_CULL_FACE);
	}

    int numvertices(0), numtriangles(0), nummaterials(0),
        numtextures(0), numnormals(0), numgroups(0);

    bool isLoaded = (model != NULL) ? true : false;
	if(isLoaded){
		if(smooth)
            glmDraw(pmodel1, GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL);
		else
            glmDraw(pmodel1, GLM_FLAT | GLM_TEXTURE | GLM_MATERIAL);

        numvertices = pmodel1->numvertices;
        numtriangles = pmodel1->numtriangles;
        nummaterials = pmodel1->nummaterials;
        numtextures = pmodel1->numtextures;
        numnormals = pmodel1->numnormals;
        numgroups = pmodel1->numgroups;
    }

    if(stats){
        renderText(20,20, isLoaded ? QString("Model is loaded") :
                   QString("Model is not loaded"), QFont("TypeWriter", 10, QFont::Bold));
        renderText(20,35,   QString("vertices: ")   + QString::number(numvertices));
        renderText(20,50,   QString("triangles: ")  + QString::number(numtriangles));
        renderText(20,65,   QString("materials: ")  + QString::number(nummaterials));
        renderText(20,80,   QString("textures: ")   + QString::number(numtextures));
        renderText(20,95,   QString("normals: ")    + QString::number(numnormals));
        renderText(20,110,  QString("groups: ")     + QString::number(numgroups));
        renderText(20,125,  QString("fps: ")        + QString::number(FPS));
    }
}

void GLWidget::resizeGL(int width, int height)
{
	windowWidth = width;
	windowHeight = height;
	aspectRatio = (double)width/(double)height;
	glViewport(0, 0, width, height);
	updateView();
}

void GLWidget::updateView()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(windowWidth > windowHeight){
		glOrtho((-0.5 + disPos)*aspectRatio, (+0.5 - disPos)*aspectRatio,
          -0.5 + disPos, +0.5 - disPos, 4.0, 15.0);
	} else {
		glOrtho(-0.5 + disPos, +0.5 - disPos, (-0.5 + disPos)/aspectRatio,
          (+0.5 - disPos)/aspectRatio, 4.0, 15.0);
	}

	glMatrixMode(GL_MODELVIEW);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
	lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		setXRotation(xRot + 8 * dy);
		setYRotation(yRot + 8 * dx);
	} else if (event->buttons() & Qt::RightButton) {
		setXRotation(xRot + 8 * dy);
		setZRotation(zRot + 8 * dx);
	}
	lastPos = event->pos();
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees / 15;

    if(event->orientation() == Qt::Vertical)
        setDistance(disPos + numSteps);

    event->accept();
}

/*======================================== PRIVATE =======================================*/

/*========================================================================================*/

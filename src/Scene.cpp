#include "Scene.hpp"
#include <QDebug>

void Scene::setMapFile(QFile &file)
{
	(void)file;
}

void Scene::initializeGL()
{
	qDebug("Scene::InitializeGL called");

	initializeOpenGLFunctions();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Scene::resizeGL(int w, int h)
{
	(void)w;
	(void)h;
}

void Scene::paintGL()
{}

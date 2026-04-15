#include "Scene.hpp"
#include <QDebug>

void Scene::setMapFile(QFile &file)
{
	(void)file;
}

const GLfloat squareVertices[] = {
	-1.0f, -1.0f,
	+1.0f, -1.0f,
	-1.0f, +1.0f,
	+1.0f, +1.0f,
};

void Scene::initializeGL()
{
	qDebug("Scene::initializeGL called");

	initializeOpenGLFunctions();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertex.glsl")) {
		qWarning() << "Vertex shader compile failed:" << shaderProgram.log();
		return;
	}

	if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragment.glsl")) {
		qWarning() << "Fragment shader compile failed:" << shaderProgram.log();
		return;
	}

	if (!shaderProgram.link()) {
		qWarning() << "Shader link failed:" << shaderProgram.log();
		return;
	}

	if (!vertexArray.create()) {
		qWarning("Failed to create vertex array object");
		return;
	}

	if (!vertexBuffer.create()) {
		qWarning("Failed to create vertex buffer");
		return;
	}

	QOpenGLVertexArrayObject::Binder vaoBinder(&vertexArray);
	vertexBuffer.bind();
	vertexBuffer.allocate(squareVertices, sizeof(squareVertices));

	shaderProgram.bind();
	const int positionAttribute = shaderProgram.attributeLocation("a_position");
	if (positionAttribute < 0) {
		qWarning("Failed to locate vertex attribute a_position");
		shaderProgram.release();
		vertexBuffer.release();
		return;
	}
	shaderProgram.enableAttributeArray(positionAttribute);
	shaderProgram.setAttributeBuffer(positionAttribute, GL_FLOAT, 0, 2, 2 * sizeof(GLfloat));
	shaderProgram.release();

	vertexBuffer.release();
}

void Scene::resizeGL(int w, int h)
{
	qDebug("Scene::resizeGL called");
	glViewport(0, 0, w, h);
}

void Scene::paintGL()
{
	qDebug("Scene::paintGL called");

	glClear(GL_COLOR_BUFFER_BIT);

	shaderProgram.bind();
	QOpenGLVertexArrayObject::Binder vaoBinder(&vertexArray);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	shaderProgram.release();
}

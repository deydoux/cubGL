#include "Scene.hpp"
#include <QDebug>

Scene::Scene(char *mapFilePath, QWidget *parent)
	: QOpenGLWidget(parent), mapFilePath(mapFilePath)
{}

void Scene::setMapFile(QFile &file)
{
	points.clear();

	QTextStream stream(&file);

	float maxX = 0;
	float maxY = 0;

	for (int y = 0; !stream.atEnd(); y++) {
		if (y > maxY)
			maxY = y;

		QString line = stream.readLine();

		for (int x = 0; x < line.length(); x++) {
			if (line[x] != '1')
				continue;

			if (x > maxX)
				maxX = x;

			points.append(QPointF(x, y));
		}
	}

	maxX = std::fmax(maxX, 1);
	maxY = std::fmax(maxY, 1);

	// Normalize to [-1, 1]
	for (QPointF &point: points) {
		float x = point.x();
		float y = point.y();

		point.setX((x / maxX) * 2.0f - 1.0f);
		point.setY((y / maxY) * 2.0f - 1.0f);
	}

	if (vertexBuffer.isCreated()) {
		QOpenGLVertexArrayObject::Binder vaoBinder(&vertexArray);
		vertexBuffer.bind();
		updateVertices(maxX, maxY);
		vertexBuffer.release();
	}

	update();
}

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
	updateVertices(1, 1);

	shaderProgram.bind();
	const int positionAttribute = shaderProgram.attributeLocation("position");
	if (positionAttribute < 0) {
		qWarning("Failed to locate vertex attribute position");
		shaderProgram.release();
		vertexBuffer.release();
		return;
	}
	shaderProgram.enableAttributeArray(positionAttribute);
	shaderProgram.setAttributeBuffer(positionAttribute, GL_FLOAT, 0, 2, 2 * sizeof(float));
	shaderProgram.release();

	vertexBuffer.release();

	QFile file(mapFilePath);
	if (!file.open(QIODevice::ReadOnly))
		qWarning() << "Failed to open map file:" << file.errorString();
	setMapFile(file);
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

	for (const QPointF &point: points) {
		shaderProgram.setUniformValue("offset", QVector2D(point));
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

	shaderProgram.release();
}

static const std::vector<float> baseSquareVertices = {
	-1.0f, -1.0f,
	+1.0f, -1.0f,
	-1.0f, +1.0f,
	+1.0f, +1.0f,
};


void Scene::updateVertices(float maxX, float maxY)
{
	std::vector<float> vertices = baseSquareVertices;

	for (auto it = vertices.begin(); it != vertices.end(); ++it) {
		*it /= maxX;
		++it;
		if (it != vertices.end())
			*it /= maxY;
	}

	vertexBuffer.allocate(vertices.data(), vertices.size() * sizeof(float));
}

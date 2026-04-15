#ifndef __SCENE_HPP__
# define __SCENE_HPP__

#include <QFile>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QPointF>
#include <QVector>

class Scene: public QOpenGLWidget, protected QOpenGLFunctions
{
public:
	void setMapFile(QFile &file);

protected:
	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;

private:
	QOpenGLShaderProgram shaderProgram;
	QOpenGLBuffer vertexBuffer;
	QOpenGLVertexArrayObject vertexArray;

	QVector<QPointF> points;
};

#endif /* __SCENE_HPP__ */

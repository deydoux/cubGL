#ifndef __SCENE_HPP__
# define __SCENE_HPP__

#include <QFile>
// #include <QOpenGLBuffer>
#include <QOpenGLFunctions>
// #include <QOpenGLShaderProgram>
// #include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>

class Scene: public QOpenGLWidget, protected QOpenGLFunctions
{
// Q_OBJECT

public:
	void setMapFile(QFile &file);

protected:
	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;
};

#endif /* __SCENE_HPP__ */

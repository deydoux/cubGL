#ifndef __UPLOADBUTTON_HPP__
# define __UPLOADBUTTON_HPP__

#include "Scene.hpp"
#include <QException>
#include <QFile>
#include <QPushButton>

class UploadButton: public QPushButton
{
public:
	UploadButton(Scene &scene);

	void openFile(const QString &path);

private:
	Scene &scene;
};

#endif /* __UPLOADBUTTON_HPP__ */

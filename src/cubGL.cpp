#include "UploadButton.hpp"
#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QWidget window;
	QVBoxLayout layout(&window);

	Scene scene(argc > 1 ? argv[1] : nullptr);
	layout.addWidget(&scene);

	UploadButton uploadButton(scene);
	layout.addWidget(&uploadButton);

	window.resize(512, 512);
	window.show();

	return app.exec();
}

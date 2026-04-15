#include "UploadButton.hpp"
#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QWidget window;
	QVBoxLayout layout(&window);

	Scene scene;
	layout.addWidget(&scene);

	UploadButton uploadButton(scene);
	if (argc > 1)
		uploadButton.openFile(argv[1]);
	layout.addWidget(&uploadButton);

	window.resize(512, 512);
	window.show();

	return app.exec();
}

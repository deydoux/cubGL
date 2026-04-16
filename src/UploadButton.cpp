#include "UploadButton.hpp"
#include <QDebug>
#include <QFileDialog>

UploadButton::UploadButton(Scene &scene)
	: QPushButton("Upload Map..."), scene(scene)
{
	connect(this, &QAbstractButton::pressed, [this]() {
		const QString path = QFileDialog::getOpenFileName();
		openFile(path);
	});
}

void UploadButton::openFile(const QString &path)
{
	QFile file(path);

	if (!file.open(QIODevice::ReadOnly))
		qWarning() << "Failed to open:" << path;
	qInfo() << "Opened:" << path;

	scene.setMapFile(file);
}

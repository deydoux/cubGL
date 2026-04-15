#include "UploadButton.hpp"
#include <QDebug>
#include <QFileDialog>

UploadButton::UploadButton(): QPushButton("Upload Map...")
{
	connect(this, &QAbstractButton::pressed, [this]() {
		const QString path = QFileDialog::getOpenFileName();
		try {
			openFile(path);
		} catch (OpenFail &e) {

		}
	});
}

std::shared_ptr<QFile> UploadButton::openFile(const QString &path)
{
	auto file = std::make_shared<QFile>(path);

	if (!file->open(QIODevice::ReadOnly))
		throw new OpenFail();

	qDebug() << "Opened:" << file->fileName();
	return file;
}

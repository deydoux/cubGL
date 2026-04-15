#include "UploadButton.hpp"
#include <QDebug>
#include <QFileDialog>

UploadButton::UploadButton(const QString &text): QPushButton(text)
{
	connect(this, &QAbstractButton::pressed, []() {
		const QString fileName = QFileDialog::getOpenFileName();
		qDebug() << "Opened:" << fileName;

	});
}

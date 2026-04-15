#ifndef __UPLOADBUTTON_HPP__
# define __UPLOADBUTTON_HPP__

#include <QException>
#include <QFile>
#include <QPushButton>

class UploadButton: public QPushButton
{
public:
	UploadButton();

	std::shared_ptr<QFile> openFile(const QString &path);

private:
	class OpenFail: public QException {
		void raise() const override { throw *this; }
	};
};

#endif /* __UPLOADBUTTON_HPP__ */

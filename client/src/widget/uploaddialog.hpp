#ifndef QBTD_WIDGET_UPLOADDIALOG_HPP
#define QBTD_WIDGET_UPLOADDIALOG_HPP

#include <QtGui/QDialog>
#include <QtCore/QUrl>

#include <memory>

namespace qbtd {
namespace widget {

class UploadDialog: public QDialog {
public:
	UploadDialog( QWidget * parent );

	bool isRemote() const;
	QByteArray getLocalFile() const;
	QUrl getURL() const;

private:
	class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif

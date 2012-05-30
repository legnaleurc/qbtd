#ifndef QBTD_WIDGET_SERVERDIALOG_HPP
#define QBTD_WIDGET_SERVERDIALOG_HPP

#include <QtGui/QDialog>

#include <memory>

namespace qbtd {
namespace widget {

class ServerDialog: public QDialog {
public:
	explicit ServerDialog( QWidget * parent );

	QString getLocalServerPath() const;

private:
	class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif

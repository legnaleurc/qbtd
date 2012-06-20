#ifndef QBTD_WIDGET_SERVERDIALOG_HPP
#define QBTD_WIDGET_SERVERDIALOG_HPP

#include <QtGui/QDialog>
#include <QtNetwork/QHostAddress>

#include <memory>

namespace qbtd {
namespace widget {

class ServerDialog: public QDialog {
public:
	explicit ServerDialog( QWidget * parent );

	bool isLocal() const;
	QString getLocalServerPath() const;
	QPair< QHostAddress, quint16 > getTCPIP() const;

private:
	class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif

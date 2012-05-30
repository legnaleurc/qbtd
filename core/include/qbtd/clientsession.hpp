#ifndef QBTD_CONTROL_CLIENTSESSION_HPP
#define QBTD_CONTROL_CLIENTSESSION_HPP

#include <QtCore/QObject>

#include <memory>

namespace qbtd {
namespace control {

class ClientSession: public QObject {
	Q_OBJECT
public:
	explicit ClientSession( QObject * parent = 0 );

	void close();
	void connectToServer( const QString & path );

signals:
	void connected();
	void disconnected();

private:
	class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif

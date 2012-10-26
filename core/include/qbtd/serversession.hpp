#ifndef QBTD_CONTROL_SERVERSESSION_HPP
#define QBTD_CONTROL_SERVERSESSION_HPP

#include "qbtd/config.hpp"

#include <QtNetwork/QLocalSocket>
#include <QtNetwork/QTcpSocket>

#include <memory>

namespace qbtd {
namespace control {

class QBTD_DLL ServerSession: public QObject {
	Q_OBJECT
public:
	void disconnectFromClient();
	void response( int id, bool result, const QVariant & data );
	void notify( const QString & event, const QVariant & data );

signals:
	void disconnected();
	void requested( int id, const QString & command, const QVariant & args );

private:
	friend class SessionServer;
	ServerSession( QLocalSocket * socket, QObject * parent );
	ServerSession( QTcpSocket * socket, QObject * parent );

	class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif

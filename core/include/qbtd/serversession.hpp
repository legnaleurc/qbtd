#ifndef QBTD_CONTROL_SERVERSESSION_HPP
#define QBTD_CONTROL_SERVERSESSION_HPP

#include <QtNetwork/QLocalSocket>
#include <QtNetwork/QTcpSocket>

#include <memory>

namespace qbtd {
namespace control {

class ServerSession: public QObject {
	Q_OBJECT
public:
	ServerSession( QLocalSocket * socket, QObject * parent );
	ServerSession( QTcpSocket * socket, QObject * parent );

	void close();
	void response( bool result, const QVariant & data );

signals:
	void disconnected();
	void requested( const QString & command, const QVariant & args );

private:
	class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif

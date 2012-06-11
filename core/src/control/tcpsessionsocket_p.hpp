#ifndef QBTD_CONTROL_TCPSESSIONSOCKET_HPP_
#define QBTD_CONTROL_TCPSESSIONSOCKET_HPP_

#include "tcpsessionsocket.hpp"

namespace qbtd {
namespace control {

class TcpSessionSocket::Private : public QObject {
	Q_OBJECT
public:
	Private( QTcpSocket * socket, TcpSessionSocket * owner );
	Private( const QHostAddress & address, TcpSessionSocket * owner );

public slots:
	void onError( QAbstractSocket::SocketError socketError );

signals:
	void error( bool stop, const QString & message );

public:
	void initialize();

	TcpSessionSocket * owner;
	QTcpSocket * socket;
	QHostAddress address;
};

}
}

#endif

#ifndef QBTD_CONTROL_SERVERSESSION_HPP
#define QBTD_CONTROL_SERVERSESSION_HPP

#include <QtNetwork/QLocalSocket>
#include <QtNetwork/QTcpSocket>

#include <memory>

namespace qbtd {
namespace control {

class ServerSession: public QObject {
public:
	ServerSession( QLocalSocket * socket, QObject * parent );
	ServerSession( QTcpSocket * socket, QObject * parent );

	void close();

private:
	class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif

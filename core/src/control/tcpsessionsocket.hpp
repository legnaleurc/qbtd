#ifndef QBTD_CONTROL_TCPSESSIONSOCKET_HPP
#define QBTD_CONTROL_TCPSESSIONSOCKET_HPP

#include "sessionsocket.hpp"

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>

#include <memory>

namespace qbtd {
namespace control {

class TcpSessionSocket: public SessionSocket {
public:
	explicit TcpSessionSocket( QTcpSocket * socket, QObject * parent = 0 );
	explicit TcpSessionSocket( const QHostAddress & address, quint16 port, QObject * parent = 0 );

	virtual bool canReadLine() const;
	virtual void close();
	virtual bool isSequential() const;
	virtual bool open( OpenMode mode );

protected:
	virtual qint64 readData( char * data, qint64 maxSize );
	virtual qint64 writeData( const char * data, qint64 maxSize );

private:
	class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif

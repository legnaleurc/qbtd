#ifndef QBTD_CONTROL_SESSIONSERVER_HPP
#define QBTD_CONTROL_SESSIONSERVER_HPP

#include "qbtd/config.hpp"

#include <QtCore/QObject>
#include <QtNetwork/QHostAddress>

#include <memory>

namespace qbtd {
namespace control {

class ServerSession;

class QBTD_DLL SessionServer: public QObject {
	Q_OBJECT
public:
	explicit SessionServer( QObject * parent = 0 );
	
	void close();
	QString errorString() const;
	bool hasPendingConnections() const;
	bool isListening() const;
	bool listen( const QString & name );
	bool listen( const QHostAddress & address, quint16 port );
	int maxPendingConnections() const;
	ServerSession * nextPendingConnection();
	void setMaxPendingConnections( int numConnections );
	bool waitForNewConnection( int msec = 0, bool * timedOut = 0 );

signals:
	void newConnection();

private:
	class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif

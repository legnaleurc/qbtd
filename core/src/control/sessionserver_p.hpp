#ifndef QBTD_CONTROL_SESSIONSERVER_HPP_
#define QBTD_CONTROL_SESSIONSERVER_HPP_

#include "qbtd/sessionserver.hpp"

#include <QtNetwork/QLocalServer>
#include <QtNetwork/QTcpServer>

#include <queue>

namespace qbtd {
namespace control {

class SessionServer::Private: public QObject {
	Q_OBJECT
public:
	Private();

public slots:
	void onNewLocalConnection();
	void onNewTcpConnection();

signals:
	void newConnection();

public:
	std::vector< std::shared_ptr< QLocalServer > > localServers;
	std::vector< std::shared_ptr< QTcpServer > > tcpServers;
	std::queue< ServerSession * > pendingSessions;
};

}
}

#endif

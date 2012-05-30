#ifndef CONTROLSERVER_HPP_
#define CONTROLSERVER_HPP_

#include "controlserver.hpp"
#include "qbtd/sessionserver.hpp"

#include <QtNetwork/QLocalServer>

namespace qbtd {
namespace control {

class ControlServer::Private : public QObject {
	Q_OBJECT
public:
	static std::unique_ptr< ControlServer, std::function< void ( ControlServer * ) > > self;
	static void destory( ControlServer * );

	Private();

public slots:
	void onNewConnection();
	void onSessionDisconnected();

public:
	SessionServer server;
	std::vector< std::shared_ptr< ServerSession > > sessions;
};

}
}

#endif

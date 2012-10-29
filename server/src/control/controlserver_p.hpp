#ifndef CONTROLSERVER_HPP_
#define CONTROLSERVER_HPP_

#include "controlserver.hpp"
#include "qbtd/sessionserver.hpp"
#include "controlsession.hpp"

#include <QtNetwork/QLocalServer>

#include <functional>

namespace qbtd {
namespace control {

class ControlServer::Private : public QObject {
	Q_OBJECT
public:
	static std::unique_ptr< ControlServer, std::function< void ( ControlServer * ) > > self;
	static void destory( ControlServer * );

	Private();

public slots:
	void onBroadcastRequired( const QString & event, const QVariant & data );
	void onNewConnection();
	void onSessionDisconnected();

public:
	SessionServer server;
	std::vector< ControlSession * > sessions;
};

}
}

#endif

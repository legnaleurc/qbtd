#ifndef QBTD_CONTROL_SERVERSESSION_HPP_
#define QBTD_CONTROL_SERVERSESSION_HPP_

#include "qbtd/serversession.hpp"
#include "sessionsocket.hpp"

#include <QtScript/QScriptEngine>

namespace qbtd {
namespace control {

class ServerSession::Private: public QObject {
	Q_OBJECT
public:
	Private( SessionSocket * socket );

public slots:
	void onDisconnected();
	void onHeaderReceived();
	void onCommandReceived();

signals:
	void disconnected();

public:
	SessionSocket * socket;
	QScriptEngine * engine;
};

}
}

#endif

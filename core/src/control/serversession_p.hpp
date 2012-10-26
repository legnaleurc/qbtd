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
	Private( SessionSocket * socket, ServerSession * host );

public slots:
	void onSynReceived();
	void onRequested();

signals:
	void disconnected();
	void requested( int id, const QString & command, const QVariant & args );

public:
	ServerSession * host;
	SessionSocket * socket;
	QScriptEngine * engine;
};

}
}

#endif

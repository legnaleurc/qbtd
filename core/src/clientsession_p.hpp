#ifndef QBTD_CONTROL_CLIENTSESSION_HPP_
#define QBTD_CONTROL_CLIENTSESSION_HPP_

#include "qbtd/clientsession.hpp"
#include "sessionsocket.hpp"

#include <QtScript/QScriptEngine>

namespace qbtd {
namespace control {

class ClientSession::Private: public QObject {
	Q_OBJECT
public:
	explicit Private();

public slots:
	void onConnected();
	void onDisconnected();

signals:
	void connected();
	void disconnected();
	void received( const QString & header );

public:
	SessionSocket * socket;
	QScriptEngine * engine;
};

}
}

#endif

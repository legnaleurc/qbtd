#ifndef QBTD_CONTROL_CLIENTSESSION_HPP_
#define QBTD_CONTROL_CLIENTSESSION_HPP_

#include "qbtd/clientsession.hpp"
#include "sessionsocket.hpp"

#include <QtCore/QAtomicInt>
#include <QtScript/QScriptEngine>

namespace qbtd {
namespace control {

class ClientSession::Private: public QObject {
	Q_OBJECT
public:
	Private();

public slots:
	void onConnected();
	void onDisconnected();
	void onAckReceived();
	void onResponse();

signals:
	void connected();
	void disconnected();
	void responsed( int id, bool result, const QVariant & data );

public:
	SessionSocket * socket;
	QScriptEngine * engine;
	QAtomicInt counter;
};

}
}

#endif

#ifndef CONTROLSESSION_HPP_
#define CONTROLSESSION_HPP_

#include "qbtd/controlsession.hpp"

#include <QtScript/QScriptEngine>

namespace qbtd {
namespace control {

class ControlSession::Private: public QObject {
	Q_OBJECT
public:
	explicit Private( QLocalSocket * socket );

public slots:
	void onConnected();
	void onDisconnected();
	void onHeaderReceived();
	void onCommandReceived();

signals:
	void connected();
	void disconnected();
	void received( const QString & header );

public:
	QLocalSocket * socket;
	QScriptEngine * engine;
};

}
}

#endif

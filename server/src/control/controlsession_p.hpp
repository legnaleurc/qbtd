#ifndef QBTD_CONTROL_CONTROLSESSION_HPP_
#define QBTD_CONTROL_CONTROLSESSION_HPP_

#include "controlsession.hpp"
#include "commandhandler.hpp"

namespace qbtd {
namespace control {

class ControlSession::Private: public QObject {
	Q_OBJECT
public:
	Private( ServerSession * session, ControlSession * host );
	virtual ~Private();

public slots:
	void onNotify( const QString & event, const QVariant & data );
	void onRequested( int id, const QString & command, const QVariant & args );

public:
	ControlSession * host;
	ServerSession * session;
	CommandHandler * commands;
};

}
}

#endif

#ifndef QBTD_CONTROL_CONTROLSESSION_HPP_
#define QBTD_CONTROL_CONTROLSESSION_HPP_

#include "controlsession.hpp"

namespace qbtd {
namespace control {

class ControlSession::Private: public QObject {
	Q_OBJECT
public:
	explicit Private( ServerSession * session, ControlSession * host );
	virtual ~Private();

public slots:
	void onRequested( const QString & command, const QVariant & args );

signals:
	void disconnected();

public:
	ControlSession * host;
	ServerSession * session;
};

}
}

#endif

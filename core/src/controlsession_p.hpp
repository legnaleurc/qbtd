#ifndef CONTROLSESSION_HPP_
#define CONTROLSESSION_HPP_

#include "qbtd/controlsession.hpp"

namespace qbtd {
namespace control {

class ControlSession::Private: public QObject {
	Q_OBJECT
public:
	explicit Private( QLocalSocket * socket );

public slots:
	void onDisconnected();

signals:
	void connected();
	void disconnected();

public:
	QLocalSocket * socket;
};

}
}

#endif

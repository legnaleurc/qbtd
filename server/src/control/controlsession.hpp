#ifndef QBTD_CONTROL_CONTROLSESSION_HPP
#define QBTD_CONTROL_CONTROLSESSION_HPP

#include <QtCore/QObject>

#include <memory>

namespace qbtd {
namespace control {

class ServerSession;

class ControlSession: public QObject {
	Q_OBJECT
public:
	explicit ControlSession( ServerSession * session, QObject * parent = 0 );

	void close();

signals:
	void disconnected();

private:
	class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif

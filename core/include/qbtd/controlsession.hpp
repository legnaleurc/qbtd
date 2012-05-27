#ifndef CONTROLSESSION_HPP
#define CONTROLSESSION_HPP

#include <QtNetwork/QLocalServer>

#include <memory>

namespace qbtd {
namespace control {

class ControlSession: public QObject {
	Q_OBJECT
public:
	ControlSession();
	explicit ControlSession( QLocalSocket * socket );

	void close();
	void connectToHost( const QString & path );

signals:
	void connected();
	void disconnected();

private:
	class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif

#ifndef QBTD_CONTROL_LOCALSESSIONSOCKET_HPP
#define QBTD_CONTROL_LOCALSESSIONSOCKET_HPP

#include "sessionsocket.hpp"

#include <QtNetwork/QLocalSocket>

#include <memory>

namespace qbtd {
namespace control {

class LocalSessionSocket: public SessionSocket {
public:
	explicit LocalSessionSocket( QLocalSocket * socket, QObject * parent = 0 );
	explicit LocalSessionSocket( const QString & path, QObject * parent = 0 );

protected:
	virtual qint64 readData( char * data, qint64 maxSize );
	virtual qint64 writeData( const char * data, qint64 maxSize );

private:
	class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif

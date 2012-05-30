#ifndef QBTD_CONTROL_LOCALSESSIONSOCKET_HPP_
#define QBTD_CONTROL_LOCALSESSIONSOCKET_HPP_

#include "localsessionsocket.hpp"

#include <QtNetwork/QLocalSocket>

namespace qbtd {
namespace control {

class LocalSessionSocket::Private : public QObject {
	Q_OBJECT
public:
	explicit Private( QLocalSocket * socket );
	explicit Private( const QString & path );

public slots:
	void onError( QLocalSocket::LocalSocketError socketError );

signals:
	void error( bool stop, const QString & message );

public:
	QLocalSocket * socket;
	QString path;
};

}
}

#endif

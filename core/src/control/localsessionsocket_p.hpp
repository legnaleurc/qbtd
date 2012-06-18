#ifndef QBTD_CONTROL_LOCALSESSIONSOCKET_HPP_
#define QBTD_CONTROL_LOCALSESSIONSOCKET_HPP_

#include "localsessionsocket.hpp"

#include <QtNetwork/QLocalSocket>

namespace qbtd {
namespace control {

class LocalSessionSocket::Private : public QObject {
	Q_OBJECT
public:
	Private( QLocalSocket * socket, LocalSessionSocket * host );
	Private( const QString & path, LocalSessionSocket * host );

public slots:
	void onError( QLocalSocket::LocalSocketError socketError );

signals:
	void error( bool stop, const QString & message );

public:
	void initialize();

	LocalSessionSocket * host;
	QLocalSocket * socket;
	QString path;
};

}
}

#endif

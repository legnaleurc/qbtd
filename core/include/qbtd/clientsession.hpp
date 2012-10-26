#ifndef QBTD_CONTROL_CLIENTSESSION_HPP
#define QBTD_CONTROL_CLIENTSESSION_HPP

#include "qbtd/config.hpp"

#include <QtCore/QObject>
#include <QtNetwork/QHostAddress>

#include <memory>

namespace qbtd {
namespace control {

class QBTD_DLL ClientSession: public QObject {
	Q_OBJECT
public:
	explicit ClientSession( QObject * parent = 0 );

	void connectToServer( const QString & path );
	void connectToServer( const QHostAddress & address, quint16 port );
	void disconnectFromServer();
	int request( const QString & command, const QVariant & args );

signals:
	void connected();
	void disconnected();
	void error( bool stop, const QString & message );
	void responsed( int id, bool result, const QVariant & data );
	void notified( const QString & event, const QVariant & data );

private:
	class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif

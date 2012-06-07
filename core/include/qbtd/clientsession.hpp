#ifndef QBTD_CONTROL_CLIENTSESSION_HPP
#define QBTD_CONTROL_CLIENTSESSION_HPP

#include <QtCore/QObject>

#include <memory>

namespace qbtd {
namespace control {

class ClientSession: public QObject {
	Q_OBJECT
public:
	explicit ClientSession( QObject * parent = 0 );

	void connectToServer( const QString & path );
	void disconnectFromServer();
	void request( const QString & command, const QVariant & args );

signals:
	void connected();
	void disconnected();
	void error( bool stop, const QString & message );
	void responsed( bool result, const QVariant & data );

private:
	class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif

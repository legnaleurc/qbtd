#ifndef QBTD_CONTROL_CONTROLSESSION_HPP
#define QBTD_CONTROL_CONTROLSESSION_HPP

#include <QtCore/QObject>
#include <QtNetwork/QHostAddress>

#include <functional>
#include <memory>

namespace qbtd {
namespace control {

class ControlSession: public QObject {
	Q_OBJECT
public:
	typedef std::function< void ( bool, const QVariant & ) > SuccessCallback;

	static void initialize();
	static ControlSession & instance();

	void connectToServer( const QString & path );
	void connectToServer( const QHostAddress & address, quint16 port );
	void disconnectFromServer();
	void request( const QString & command, const QVariant & args, SuccessCallback success );

signals:
	void connected();
	void disconnected();
	void error( bool stop, const QString & message );

private:
	ControlSession();
	ControlSession( const ControlSession & );
	ControlSession & operator =( const ControlSession & );
	virtual ~ControlSession();
	class Private;
	friend class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif

#ifndef QBTD_CONTROL_CONTROLSERVER_HPP
#define QBTD_CONTROL_CONTROLSERVER_HPP

#include <QtNetwork/QHostAddress>

#include <memory>

namespace qbtd {
namespace control {

class ControlServer {
public:
	static void initialize();
	static ControlServer & instance();

	bool listen( const QString & path );
	bool listen( const QHostAddress & address );

private:
	ControlServer();
	~ControlServer();
	ControlServer( const ControlServer & );
	ControlServer & operator =( const ControlServer & );
	class Private;
	friend class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif

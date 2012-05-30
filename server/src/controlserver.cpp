#include "controlserver_p.hpp"
#include "qbtd/serversession.hpp"

#include <QtCore/QtDebug>

#include <cassert>

using qbtd::control::ControlServer;

std::unique_ptr< ControlServer, std::function< void ( ControlServer * ) > > ControlServer::Private::self;

void ControlServer::Private::destory( ControlServer * data ) {
	delete data;
}

// TODO local socket, ipv4, ipv6 version
ControlServer::Private::Private():
server(),
sessions() {
	this->connect( &this->server, SIGNAL( newConnection() ), SLOT( onNewConnection() ) );
}

void ControlServer::Private::onNewConnection() {
	while( this->server.hasPendingConnections() ) {
		auto session = std::shared_ptr< ServerSession >( this->server.nextPendingConnection(), []( ServerSession * data )->void {
			QMetaObject::invokeMethod( data, "deleteLater" );
		} );
		this->sessions.push_back( session );
	}
}

void ControlServer::Private::onSessionDisconnected() {
	ServerSession * session = static_cast< ServerSession * >( this->sender() );
	auto it = std::remove_if( this->sessions.begin(), this->sessions.end(), [session]( decltype( this->sessions[0] ) s )->bool {
		return session == s.get();
	} );
	this->sessions.erase( it, this->sessions.end() );
}

void ControlServer::initialize() {
	if( Private::self ) {
		return;
	}
	Private::self.reset( new ControlServer );
	Private::self.get_deleter() = Private::destory;
}

ControlServer & ControlServer::instance() {
	if( !Private::self ) {
		assert( !"not initialized" );
	}
	return *Private::self;
}

ControlServer::ControlServer():
p_( new Private ) {
}

ControlServer::~ControlServer() {
	// stop listen control session
	this->p_->server.close();
	// disconnect all session
	for( auto it = this->p_->sessions.begin(); it != this->p_->sessions.end(); ++it ) {
		( *it )->close();
	}
}

bool ControlServer::listen( const QString & path ) {
	return this->p_->server.listen( path );
}

bool ControlServer::listen( const QHostAddress & address ) {
	return false;
}

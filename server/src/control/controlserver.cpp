#include "controlserver_p.hpp"
#include "qbtd/serversession.hpp"

#include <QtCore/QtDebug>

#include <algorithm>
#include <cassert>

namespace {
struct Helper {
	Helper( qbtd::control::ControlSession * session ): session( session ) {
	}
	bool operator()( qbtd::control::ControlSession * s ) const {
		return this->session == s;
	}
	qbtd::control::ControlSession * session;
};
}

using qbtd::control::ControlServer;

std::unique_ptr< ControlServer, std::function< void ( ControlServer * ) > > ControlServer::Private::self( NULL, &Private::destory );

void ControlServer::Private::destory( ControlServer * data ) {
	delete data;
}

ControlServer::Private::Private():
server(),
sessions() {
	this->connect( &this->server, SIGNAL( newConnection() ), SLOT( onNewConnection() ) );
}

void ControlServer::Private::onNewConnection() {
	while( this->server.hasPendingConnections() ) {
		ControlSession * session = new ControlSession( this->server.nextPendingConnection(), this );
		this->connect( session, SIGNAL( disconnected() ), SLOT( onSessionDisconnected() ) );
		this->sessions.push_back( session );
	}
}

void ControlServer::Private::onSessionDisconnected() {
	ControlSession * session = static_cast< ControlSession * >( this->sender() );
	assert( session != NULL || !"ControlSession casting failed" );
	auto it = std::remove_if( this->sessions.begin(), this->sessions.end(), Helper( session ) );
	for( auto iit = it; iit != this->sessions.end(); ++iit ) {
		( *iit )->deleteLater();
	}
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
		// NOTE this slot will modify this->p_->sessions, so this **MUST** disconnect first
		( *it )->disconnect( SIGNAL( disconnected() ), this->p_.get(), SLOT( onSessionDisconnected() ) );
		( *it )->close();
		( *it )->deleteLater();
	}
}

bool ControlServer::listen( const QString & path ) {
	return this->p_->server.listen( path );
}

bool ControlServer::listen( const QHostAddress & address, quint16 port ) {
	return this->p_->server.listen( address, port );
}

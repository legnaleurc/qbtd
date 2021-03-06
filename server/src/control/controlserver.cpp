#include "controlserver_p.hpp"
#include "qbtd/serversession.hpp"

#include <QtCore/QtDebug>

#include <cassert>
#include <algorithm>

using qbtd::control::ControlServer;

std::unique_ptr< ControlServer, std::function< void ( ControlServer * ) > > ControlServer::Private::self;

void ControlServer::Private::destory( ControlServer * data ) {
	delete data;
}

ControlServer::Private::Private():
server(),
sessions() {
	this->connect( &this->server, SIGNAL( newConnection() ), SLOT( onNewConnection() ) );
}

void ControlServer::Private::onBroadcastRequired( const QString & event, const QVariant & data ) {
	std::for_each( this->sessions.begin(), this->sessions.end(), [&event, &data]( ControlSession * s )->void {
		s->notify( event, data );
	} );
}

void ControlServer::Private::onNewConnection() {
	while( this->server.hasPendingConnections() ) {
		ControlSession * session = new ControlSession( this->server.nextPendingConnection(), this );
		this->connect( session, SIGNAL( broadcastRequired( const QString &, const QVariant & ) ), SLOT( onBroadcastRequired( const QString &, const QVariant & ) ) );
		this->connect( session, SIGNAL( disconnected() ), SLOT( onSessionDisconnected() ) );
		this->sessions.push_back( session );
	}
}

void ControlServer::Private::onSessionDisconnected() {
	ControlSession * session = static_cast< ControlSession * >( this->sender() );
	assert( session != nullptr || !"ControlSession casting failed" );
	auto it = std::remove_if( this->sessions.begin(), this->sessions.end(), [session]( ControlSession * s )->bool {
		return session == s;
	} );
	std::for_each( it, this->sessions.end(), []( ControlSession * s )->void {
		s->deleteLater();
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

void ControlServer::progressChanged( const QByteArray & infoHash, qreal progress ) {
	QVariantMap data;
	data.insert( "info_hash", infoHash );
	data.insert( "progress", progress );
	this->p_->onBroadcastRequired( "progress_updated", data );
}

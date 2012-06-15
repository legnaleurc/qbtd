#include "sessionserver_p.hpp"
#include "qbtd/serversession.hpp"

#include <QtCore/QEventLoop>
#include <QtCore/QTimer>
#include <QtCore/QFile>

#include <cassert>

using qbtd::control::SessionServer;
using qbtd::control::ServerSession;

SessionServer::Private::Private():
localServers(),
tcpServers(),
pendingSessions() {
}

void SessionServer::Private::onNewLocalConnection() {
	QLocalServer * server = dynamic_cast< QLocalServer * >( this->sender() );
	assert( server || !"QLocalServer casting failed" );
	while( server->hasPendingConnections() ) {
		QLocalSocket * socket = server->nextPendingConnection();
		ServerSession * session = new ServerSession( socket, this );
		this->pendingSessions.push( session );
	}
	emit this->newConnection();
}

void SessionServer::Private::onNewTcpConnection() {
	QTcpServer * server = dynamic_cast< QTcpServer * >( this->sender() );
	assert( server || !"QTcpServer casting failed" );
	while( server->hasPendingConnections() ) {
		QTcpSocket * socket = server->nextPendingConnection();
		ServerSession * session = new ServerSession( socket, this );
		this->pendingSessions.push( session );
	}
	emit this->newConnection();
}

SessionServer::SessionServer( QObject * parent ):
QObject( parent ),
p_( new Private ) {
	this->connect( this->p_.get(), SIGNAL( newConnection() ), SIGNAL( newConnection() ) );
}

void SessionServer::close() {
	for( auto it = this->p_->localServers.begin(); it != this->p_->localServers.end(); ++it ) {
		( *it )->close();
	}
	this->p_->localServers.clear();
	for( auto it = this->p_->tcpServers.begin(); it != this->p_->tcpServers.end(); ++it ) {
		( *it )->close();
	}
	this->p_->tcpServers.clear();
}

QString SessionServer::errorString() const {
	return QString();
}

bool SessionServer::hasPendingConnections() const {
	return !this->p_->pendingSessions.empty();
}

bool SessionServer::isListening() const {
	return !this->p_->localServers.empty() || !this->p_->tcpServers.empty();
}

bool SessionServer::listen( const QString & name ) {
	auto server = std::make_shared< QLocalServer >();
	bool listened = server->listen( name );

	if( server->serverError() == QAbstractSocket::AddressInUseError ) {
		// cleanup previous garbage
		QFile::remove( name );
		listened = server->listen( name );
	}
	if( listened ) {
		this->p_->connect( server.get(), SIGNAL( newConnection() ), SLOT( onNewLocalConnection() ) );
		this->p_->localServers.push_back( server );
	}
	return listened;
}

bool SessionServer::listen( const QHostAddress & address ) {
	auto server = std::make_shared< QTcpServer >();
	bool listened = server->listen( address );
	if( listened ) {
		this->p_->connect( server.get(), SIGNAL( newConnection() ), SLOT( onNewTcpConnection() ) );
		this->p_->tcpServers.push_back( server );
	}
	return listened;
}

int SessionServer::maxPendingConnections() const {
	return -1;
}

ServerSession * SessionServer::nextPendingConnection() {
	if( this->p_->pendingSessions.empty() ) {
		return NULL;
	}
	ServerSession * session = this->p_->pendingSessions.front();
	this->p_->pendingSessions.pop();
	return session;
}

void SessionServer::setMaxPendingConnections( int numConnections ) {
}

bool SessionServer::waitForNewConnection( int msec, bool * timedOut ) {
	QEventLoop wait;
	QTimer timer;
	timer.setSingleShot( true );
	timer.setInterval( msec );
	wait.connect( &timer, SIGNAL( timeout() ), SLOT( quit() ) );
	wait.connect( this, SIGNAL( newConnection() ), SLOT( quit() ) );
	wait.exec();
	if( !timer.isActive() ) {
		// timer timeout
		if( timedOut != NULL ) {
			*timedOut = true;
		}
		return false;
	} else {
		// new connections
		if( timedOut != NULL ) {
			*timedOut = false;
		}
		timer.stop();
		return true;
	}
}

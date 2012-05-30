#include "localsessionsocket_p.hpp"

using qbtd::control::LocalSessionSocket;

LocalSessionSocket::Private::Private( QLocalSocket * socket ):
socket( socket ),
path( socket->fullServerName() ) {
	this->connect( socket, SIGNAL( error( QLocalSocket::LocalSocketError ) ), SLOT( onError( QLocalSocket::LocalSocketError ) ) );
}

LocalSessionSocket::Private::Private( const QString & path ):
socket( new QLocalSocket( this ) ),
path( path ) {
	this->connect( socket, SIGNAL( error( QLocalSocket::LocalSocketError ) ), SLOT( onError( QLocalSocket::LocalSocketError ) ) );
}

void LocalSessionSocket::Private::onError( QLocalSocket::LocalSocketError socketError ) {
	emit this->error( true, this->socket->errorString() );
}

LocalSessionSocket::LocalSessionSocket( QLocalSocket * socket, QObject * parent ):
SessionSocket( parent ),
p_( new Private( socket ) ) {
	this->connect( this->p_.get(), SIGNAL( error( bool, const QString & ) ), SIGNAL( error( bool, const QString & ) ) );
}

LocalSessionSocket::LocalSessionSocket( const QString & path, QObject * parent ):
SessionSocket( parent ),
p_( new Private( path ) ) {
	this->connect( this->p_.get(), SIGNAL( error( bool, const QString & ) ), SIGNAL( error( bool, const QString & ) ) );
}

qint64 LocalSessionSocket::readData( char * data, qint64 maxSize ) {
	// TODO check link status
	QByteArray buffer = this->p_->socket->read( maxSize );
	qstrncpy( data, buffer, maxSize );
	return buffer.size();
}

qint64 LocalSessionSocket::writeData( const char * data, qint64 maxSize ) {
	// TODO check link status
	return this->p_->socket->write( data, maxSize );
}

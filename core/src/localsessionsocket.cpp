#include "localsessionsocket_p.hpp"

using qbtd::control::LocalSessionSocket;

LocalSessionSocket::Private::Private( QLocalSocket * socket, LocalSessionSocket * host ):
host( host ),
socket( socket ),
path( socket->fullServerName() ) {
	this->socket->setParent( this );
	this->initialize();
	this->host->QIODevice::open( QIODevice::ReadWrite );
}

LocalSessionSocket::Private::Private( const QString & path, LocalSessionSocket * host ):
host( host ),
socket( new QLocalSocket( this ) ),
path( path ) {
	this->initialize();
}

void LocalSessionSocket::Private::initialize() {
	this->connect( socket, SIGNAL( error( QLocalSocket::LocalSocketError ) ), SLOT( onError( QLocalSocket::LocalSocketError ) ) );

	this->host->connect( this, SIGNAL( error( bool, const QString & ) ), SIGNAL( error( bool, const QString & ) ) );
	this->host->connect( this->socket, SIGNAL( connected() ), SIGNAL( opened() ) );
	this->host->connect( this->socket, SIGNAL( disconnected() ), SIGNAL( closed() ) );
	this->host->connect( this->socket, SIGNAL( aboutToClose() ), SIGNAL( aboutToClose() ) );
	this->host->connect( this->socket, SIGNAL( bytesWritten( qint64 ) ), SIGNAL( bytesWritten( qint64 ) ) );
	this->host->connect( this->socket, SIGNAL( readChannelFinished() ), SIGNAL( readChannelFinished() ) );
	this->host->connect( this->socket, SIGNAL( readyRead() ), SIGNAL( readyRead() ) );
}

void LocalSessionSocket::Private::onError( QLocalSocket::LocalSocketError socketError ) {
	this->host->setErrorString( this->socket->errorString() );
	emit this->error( true, this->socket->errorString() );
}

LocalSessionSocket::LocalSessionSocket( QLocalSocket * socket, QObject * parent ):
SessionSocket( parent ),
p_( new Private( socket, this ) ) {
}

LocalSessionSocket::LocalSessionSocket( const QString & path, QObject * parent ):
SessionSocket( parent ),
p_( new Private( path, this ) ) {
}

bool LocalSessionSocket::canReadLine() const {
	return this->QIODevice::canReadLine() || this->p_->socket->canReadLine();
}

void LocalSessionSocket::close() {
	this->p_->socket->disconnectFromServer();
}

bool LocalSessionSocket::isSequential() const {
	return this->p_->socket->isSequential();
}

bool LocalSessionSocket::open( OpenMode mode ) {
	if( mode != QIODevice::ReadWrite ) {
		return false;
	}
	bool opened = this->QIODevice::open( mode );
	this->p_->socket->connectToServer( this->p_->path, mode );
	return opened;
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

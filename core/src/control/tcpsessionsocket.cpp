#include "tcpsessionsocket_p.hpp"

#include <cstring>

using qbtd::control::TcpSessionSocket;

TcpSessionSocket::Private::Private( QTcpSocket * socket, TcpSessionSocket * owner ):
owner( owner ),
socket( socket ),
address( socket->peerAddress() ) {
	this->socket->setParent( this );
	this->initialize();
	this->owner->QIODevice::open( QIODevice::ReadWrite );
}

TcpSessionSocket::Private::Private( const QHostAddress & address, TcpSessionSocket * owner ):
owner( owner ),
socket( new QTcpSocket( this ) ),
address( address ) {
	this->initialize();
}

void TcpSessionSocket::Private::initialize() {
	this->connect( socket, SIGNAL( error( QAbstractSocket::SocketError ) ), SLOT( onError( QAbstractSocket::SocketError ) ) );

	this->owner->connect( this, SIGNAL( error( bool, const QString & ) ), SIGNAL( error( bool, const QString & ) ) );
	this->owner->connect( this->socket, SIGNAL( connected() ), SIGNAL( opened() ) );
	this->owner->connect( this->socket, SIGNAL( disconnected() ), SIGNAL( closed() ) );
	this->owner->connect( this->socket, SIGNAL( aboutToClose() ), SIGNAL( aboutToClose() ) );
	this->owner->connect( this->socket, SIGNAL( bytesWritten( qint64 ) ), SIGNAL( bytesWritten( qint64 ) ) );
	this->owner->connect( this->socket, SIGNAL( readChannelFinished() ), SIGNAL( readChannelFinished() ) );
	this->owner->connect( this->socket, SIGNAL( readyRead() ), SIGNAL( readyRead() ) );
}

void TcpSessionSocket::Private::onError( QAbstractSocket::SocketError socketError ) {
	this->owner->setErrorString( this->socket->errorString() );

	switch( this->socket->error() ) {
	case QAbstractSocket::SocketTimeoutError:
	case QAbstractSocket::DatagramTooLargeError:
		// TODO discard buffer
		emit this->error( false, this->socket->errorString() );
		break;
	default:
		// QLocalSocket will be closed or not connected, so we must close buffer
		this->host->QIODevice::close();
		emit this->error( true, this->socket->errorString() );
		break;
	}
}

TcpSessionSocket::TcpSessionSocket( QTcpSocket * socket, QObject * parent ):
SessionSocket( parent ),
p_( new Private( socket, this ) ) {
}

TcpSessionSocket::TcpSessionSocket( const QHostAddress & address, QObject * parent ):
SessionSocket( parent ),
p_( new Private( address, this ) ) {
}

bool TcpSessionSocket::canReadLine() const {
	return this->QIODevice::canReadLine() || this->p_->socket->canReadLine();
}

void TcpSessionSocket::close() {
	this->p_->socket->disconnectFromHost();
}

bool TcpSessionSocket::isSequential() const {
	return this->p_->socket->isSequential();
}

bool TcpSessionSocket::open( OpenMode mode ) {
	if( mode != QIODevice::ReadWrite ) {
		return false;
	}
	bool opened = this->QIODevice::open( mode );
	this->p_->socket->connectToHost( this->p_->address, mode );
	return opened;
}

qint64 TcpSessionSocket::readData( char * data, qint64 maxSize ) {
	// TODO check link status
	QByteArray buffer = this->p_->socket->read( maxSize );
	std::memcpy( data, buffer, maxSize );
	return buffer.size();
}

qint64 TcpSessionSocket::writeData( const char * data, qint64 maxSize ) {
	// TODO check link status
	return this->p_->socket->write( data, maxSize );
}

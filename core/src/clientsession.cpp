#include "clientsession_p.hpp"
#include "localsessionsocket.hpp"

using qbtd::control::ClientSession;

ClientSession::Private::Private():
QObject(),
socket( nullptr ),
engine( new QScriptEngine( this ) ) {
}

void ClientSession::Private::onDisconnected() {
	QMetaObject::invokeMethod( this->socket, "deleteLater" );

	emit this->disconnected();
}

void ClientSession::Private::onConnected() {
	this->connect( this->socket, SIGNAL( readyRead() ), SLOT( onHeaderReceived() ) );
	this->socket->write( "=0\n" );
}

ClientSession::ClientSession( QObject * parent ):
QObject( parent ),
p_( new Private ) {
}

void ClientSession::close() {
	this->p_->socket->close();
}

void ClientSession::connectToServer( const QString & path ) {
	this->p_->socket = new LocalSessionSocket( path, this );
	this->p_->connect( this->p_->socket, SIGNAL( connected() ), SLOT( onConnected() ) );
	this->p_->connect( this->p_->socket, SIGNAL( disconnected() ), SLOT( onDisconnected() ) );
	this->p_->socket->open( QIODevice::ReadWrite );
}

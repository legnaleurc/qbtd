#include "controlsession_p.hpp"

#include <QtNetwork/QLocalSocket>

using qbtd::control::ControlSession;

ControlSession::Private::Private( QLocalSocket * socket ):
socket( socket ) {
	this->connect( this->socket, SIGNAL( disconnected() ), SLOT( onDisconnected() ) );
}

void ControlSession::Private::onDisconnected() {
	QMetaObject::invokeMethod( this->socket, "deleteLater" );

	emit this->disconnected();
}

ControlSession::ControlSession():
p_( new Private( new QLocalSocket( this ) ) ) {
}

ControlSession::ControlSession( QLocalSocket * socket ):
p_( new Private( socket ) ) {
	this->connect( this->p_.get(), SIGNAL( disconnected() ), SIGNAL( disconnected() ) );
}

void ControlSession::close() {
	this->p_->socket->close();
}
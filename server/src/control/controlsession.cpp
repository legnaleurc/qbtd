#include "controlsession_p.hpp"
#include "qbtd/serversession.hpp"
#include "qbtd/jsonerror.hpp"

#include <QtCore/QtDebug>

using qbtd::control::ControlSession;
using qbtd::control::ServerSession;
using qbtd::exception::JsonError;

ControlSession::Private::Private( ServerSession * session, ControlSession * host ):
host( host ),
session( session ),
commands( new CommandHandler( this ) ) {
	this->session->setParent( this );
	this->host->connect( this->session, SIGNAL( disconnected() ), SIGNAL( disconnected() ) );
	this->connect( this->commands, SIGNAL( notify( const QString &, const QVariant & ) ), SLOT( onNotify( const QString &, const QVariant & ) ) );
	this->connect( this->session, SIGNAL( requested( int, const QString &, const QVariant & ) ), SLOT( onRequested( int, const QString &, const QVariant & ) ) );
}

ControlSession::Private::~Private() {
	this->session->deleteLater();
}

void ControlSession::Private::onNotify( const QString & event, const QVariant & data ) {
	qDebug() << event << data;
	try {
		this->session->notify( event, data );
	} catch( JsonError & e ) {
		this->session->notify( QString( "critical" ), QString( "server can not encode response" ) );
	}
}

void ControlSession::Private::onRequested( int id, const QString & command, const QVariant & args ) {
	qDebug() << id << command << args;
	auto response = this->commands->execute( command, args );
	try {
		this->session->response( id, response.first, response.second );
	} catch( JsonError & e ) {
		this->session->response( id, false, QString( "server can not encode response" ) );
	}
}

ControlSession::ControlSession( ServerSession * session, QObject * parent ):
QObject( parent ),
p_( new Private( session, this ) ) {
	this->connect( this->p_->commands, SIGNAL( broadcast( const QString &, const QVariant & ) ), SIGNAL( broadcastRequired( const QString &, const QVariant & ) ) );
}

void ControlSession::close() {
	this->p_->session->disconnectFromClient();
}

void ControlSession::notify( const QString & event, const QVariant & data ) const {
	this->p_->onNotify( event, data );
}

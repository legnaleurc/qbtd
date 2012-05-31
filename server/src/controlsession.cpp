#include "controlsession_p.hpp"
#include "qbtd/serversession.hpp"

#include <QtCore/QtDebug>

using qbtd::control::ControlSession;

ControlSession::Private::Private( ServerSession * session, ControlSession * host ):
host( host ),
session( session ) {
	this->session->setParent( this );
	this->host->connect( this->session, SIGNAL( disconnected() ), SIGNAL( disconnected() ) );
	this->connect( this->session, SIGNAL( requested( const QString &, const QVariant & ) ), SLOT( onRequested( const QString &, const QVariant & ) ) );
}

ControlSession::Private::~Private() {
	this->session->deleteLater();
}

void ControlSession::Private::onRequested( const QString & command, const QVariant & args ) {
	qDebug() << command << args;
	this->session->response( false, QVariant() );
}

ControlSession::ControlSession( ServerSession * session, QObject * parent ):
QObject( parent ),
p_( new Private( session, this ) ) {
}

void ControlSession::close() {
	this->p_->session->close();
}

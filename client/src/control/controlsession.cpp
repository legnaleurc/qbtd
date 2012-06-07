#include "controlsession_p.hpp"

#include <cassert>

#include <QtCore/QtDebug>

using qbtd::control::ControlSession;

std::unique_ptr< ControlSession, std::function< void ( ControlSession * ) > > ControlSession::Private::self;

void ControlSession::Private::destroy( ControlSession * data ) {
	delete data;
}

ControlSession::Private::Private():
QObject(),
session( new ClientSession( this ) ),
success() {
	this->connect( this->session, SIGNAL( responsed( bool, const QVariant & ) ), SLOT( onResponsed( bool, const QVariant & ) ) );
}

void ControlSession::Private::onResponsed( bool result, const QVariant & data ) {
	qDebug() << __PRETTY_FUNCTION__ << result << data;
	this->success( result, data );
	this->success = nullptr;
}

void ControlSession::initialize() {
	if( Private::self ) {
		return;
	}
	Private::self.reset( new ControlSession );
	Private::self.get_deleter() = &Private::destroy;
}

ControlSession & ControlSession::instance() {
	if( !Private::self ) {
		assert( !"ControlSession not initialized" );
	}
	return *Private::self;
}

ControlSession::ControlSession():
QObject(),
p_( new Private ) {
	this->connect( this->p_->session, SIGNAL( connected() ), SIGNAL( connected() ) );
	this->connect( this->p_->session, SIGNAL( disconnected() ), SIGNAL( disconnected() ) );
	this->connect( this->p_->session, SIGNAL( error( bool, const QString & ) ), SIGNAL( error( bool, const QString & ) ) );
}

ControlSession::~ControlSession() {
}

void ControlSession::connectToServer( const QString & path ) {
	this->p_->session->connectToServer( path );
}

void ControlSession::disconnectFromServer() {
	this->p_->session->close();
}

void ControlSession::request( const QString & command, const QVariant & args, SuccessCallback success ) {
	if( !this->p_->success ) {
		return;
	}
	this->p_->success = success;
	this->p_->session->request( command, args );
}

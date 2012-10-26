#include "controlsession_p.hpp"
#include "qbtd/jsonerror.hpp"

#include <cassert>

using qbtd::control::ControlSession;
using qbtd::exception::JsonError;

std::unique_ptr< ControlSession, std::function< void ( ControlSession * ) > > ControlSession::Private::self;

void ControlSession::Private::destroy( ControlSession * data ) {
	delete data;
}

ControlSession::Private::Private():
QObject(),
lock(),
session( new ClientSession( this ) ),
handlers() {
	this->connect( this->session, SIGNAL( responsed( int, bool, const QVariant & ) ), SLOT( onResponsed( int, bool, const QVariant & ) ) );
}

// TODO handle id=0
void ControlSession::Private::onResponsed( int id, bool result, const QVariant & data ) {
	QWriteLocker locker( &this->lock );
	Q_UNUSED( locker )
	auto it = this->handlers.find( id );
	if( it == this->handlers.end() ) {
		// id not found
		// TODO warning message
		return;
	}
	if( it->second ) {
		// some actions do not have success callback
		it->second( result, data );
	}
	this->handlers.erase( it );
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

void ControlSession::connectToServer( const QHostAddress & address, quint16 port ) {
	this->p_->session->connectToServer( address, port );
}

void ControlSession::disconnectFromServer() {
	this->p_->session->disconnectFromServer();
}

void ControlSession::request( const QString & command, const QVariant & args, SuccessCallback success ) {
	try {
		int id = this->p_->session->request( command, args );
		QWriteLocker locker( &this->p_->lock );
		Q_UNUSED( locker )
		this->p_->handlers.insert( std::make_pair( id, success ) );
	} catch( JsonError & e ) {
		emit this->error( false, QObject::tr( "Can not encode request: %1" ).arg( e.getMessage() ) );
	}
}

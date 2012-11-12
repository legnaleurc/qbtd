#include "controlsession_p.hpp"
#include "qbtd/jsonerror.hpp"
#include "model/torrentinfo.hpp"

#include <cassert>

using qbtd::control::ControlSession;
using qbtd::model::TorrentInfo;

std::unique_ptr< ControlSession, std::function< void ( ControlSession * ) > > ControlSession::Private::self;

void ControlSession::Private::destroy( ControlSession * data ) {
	delete data;
}

ControlSession::Private::Private():
QObject(),
lock(),
session( new ClientSession( this ) ),
responseHandlers(),
notifyHandlers() {
	this->connect( this->session, SIGNAL( notified( const QString &, const QVariant & ) ), SLOT( onNotified( const QString &, const QVariant & ) ) );
	this->connect( this->session, SIGNAL( responsed( int, bool, const QVariant & ) ), SLOT( onResponsed( int, bool, const QVariant & ) ) );

	this->notifyHandlers.insert( "torrent_added", [this]( const QVariant & data )->void {
		auto torrent = data.toMap();
		emit this->torrentAdded( TorrentInfo( torrent ) );
	} );
}

int ControlSession::Private::request( const QString & command, const QVariant & args, ResponseCallback success ) {
	int id = this->session->request( command, args );
	QWriteLocker locker( &this->lock );
	Q_UNUSED( locker )
	this->responseHandlers.insert( std::make_pair( id, success ) );
	return id;
}

void ControlSession::Private::onNotified( const QString & event, const QVariant & data ) {
	auto it = this->notifyHandlers.find( event );
	if( it == this->notifyHandlers.end() ) {
		// event not supported
		// TODO warning message
		return;
	}
	assert( it.value() || !"invalid notifier handler" );
	it.value()( data );
}

void ControlSession::Private::onResponsed( int id, bool result, const QVariant & data ) {
	QWriteLocker locker( &this->lock );
	Q_UNUSED( locker )
	auto it = this->responseHandlers.find( id );
	if( it == this->responseHandlers.end() ) {
		// id not found
		// TODO warning message
		return;
	}
	if( it->second ) {
		// some actions do not have success callback
		it->second( result, data );
	}
	this->responseHandlers.erase( it );
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

	this->connect( this->p_.get(), SIGNAL( torrentAdded( const qbtd::model::TorrentInfo & ) ), SIGNAL( torrentAdded( const qbtd::model::TorrentInfo & ) ) );
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

int ControlSession::addTorrentFile( const QString & filePath ) {
	return this->p_->request( "add", filePath, [this]( bool result, const QVariant & data )->void {
		if( !result ) {
			// TODO emit error
			return;
		}
		emit this->torrentFileAdded();
	} );
}

int ControlSession::addTorrentUrl( const QUrl & url ) {
	return this->p_->request( "add_from_url", url, [this]( bool result, const QVariant & data )->void {
		if( !result ) {
			// TODO emit error
			return;
		}
		emit this->torrentUrlAdded();
	} );
}

int ControlSession::list() {
	return this->p_->request( "list", QVariant(), [this]( bool result, const QVariant & data )->void {
		if( !result ) {
			// TODO emit error
			return;
		}
		auto torrents = data.toList();
		using qbtd::model::TorrentInfo;
		QList< TorrentInfo > result_;
		std::for_each( torrents.begin(), torrents.end(), [&result_]( const QVariant & data_ )->void {
			using qbtd::model::TorrentInfo;
			result_.append( TorrentInfo( data_.toMap() ) );
		} );
		emit this->listed( result_ );
	} );
}

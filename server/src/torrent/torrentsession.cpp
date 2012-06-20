#include "torrentsession_p.hpp"
#include "exception/torrentexception.hpp"

#include <QtCore/QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QTimer>
#include <QtCore/QEventLoop>

using qbtd::torrent::TorrentSession;
using qbtd::exception::TorrentException;

std::unique_ptr< TorrentSession, std::function< void ( TorrentSession * ) > > TorrentSession::Private::self;

void TorrentSession::Private::destory( TorrentSession * data ) {
	delete data;
}

TorrentSession::Private::Private():
session() {
}

void TorrentSession::initialize() {
	if( Private::self != nullptr ) {
		return;
	}
	Private::self.reset( new TorrentSession );
	Private::self.get_deleter() = Private::destory;
}

TorrentSession & TorrentSession::instance() {
	if( Private::self == nullptr ) {
		assert( !"not initialized" );
	}
	return *Private::self;
}

TorrentSession::TorrentSession():
p_( new Private ) {
	// TODO read from configure
	this->p_->session.listen_on( std::make_pair( 6881, 6889 ) );
}

TorrentSession::~TorrentSession() {
}

void TorrentSession::addTorrent( const QByteArray & data ) {
	libtorrent::lazy_entry e;
	int ret = libtorrent::lazy_bdecode( data.data(), data.data() + data.size(), e );
	if( ret != 0 ) {
		throw TorrentException( "bdecode failed" );
	}
	libtorrent::add_torrent_params p;
	// TODO read from configure
	p.save_path = "/tmp";
	p.ti = new libtorrent::torrent_info( e );
	libtorrent::torrent_handle th = this->p_->session.add_torrent( p );
}

// FIXME this method blocks MAIN thread
void TorrentSession::addTorrent( const QUrl & url ) {
	if( url.scheme() != "http" && url.scheme() != "https" ) {
		throw TorrentException( QString( "can not fetch torrent from %1" ).arg( url.toString() ) );
	}

	QNetworkAccessManager nam;
	QNetworkRequest request( url );
	QNetworkReply * reply = nam.get( request );
	QEventLoop wait;
	wait.connect( reply, SIGNAL( finished() ), SLOT( quit() ) );
	wait.connect( reply, SIGNAL( error( QNetworkReply::NetworkError ) ), SLOT( quit() ) );
	wait.connect( reply, SIGNAL( sslErrors( const QList< QSslError > & errors ) ), SLOT( quit() ) );
	QTimer::singleShot( 10000, &wait, SLOT( quit() ) );
	wait.exec();

	if( reply->error() != QNetworkReply::NoError ) {
		reply->deleteLater();
		throw TorrentException( QString( "can not fetch torrent because %1" ).arg( reply->errorString() ) );
	}
	QByteArray torrent = reply->readAll();
	reply->deleteLater();
	this->addTorrent( torrent );
}

QVariantList TorrentSession::listTorrent() const {
	std::vector< libtorrent::torrent_handle > ths = this->p_->session.get_torrents();
	QVariantList l;
	for( auto it = ths.begin(); it != ths.end(); ++it ) {
		QVariantMap m;
		m.insert( "name", QString::fromStdString( it->name() ) );
		libtorrent::torrent_status status = it->status();
		m.insert( "progress", static_cast< double >( status.progress ) );
		l.append( m );
	}
	return l;
}

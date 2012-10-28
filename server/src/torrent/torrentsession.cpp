#include "torrentsession_p.hpp"
#include "exception/torrentexception.hpp"
#include "qbtd/settings.hpp"

#include <QtCore/QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QSslError>

using qbtd::torrent::TorrentSession;
using qbtd::exception::TorrentException;
using qbtd::utility::Settings;

std::unique_ptr< TorrentSession, std::function< void ( TorrentSession * ) > > TorrentSession::Private::self;

void TorrentSession::Private::destory( TorrentSession * data ) {
	delete data;
}

TorrentSession::Private::Private():
QObject(),
session(),
nam() {
}

void TorrentSession::Private::onTorrentFileReady() {
	QNetworkReply * reply = static_cast< QNetworkReply * >( this->sender() );
	QByteArray torrent = reply->readAll();
	reply->deleteLater();
	try {
		self->addTorrent( torrent );
	} catch( TorrentException & e ) {
		emit this->error( e.getMessage() );
	}
}

void TorrentSession::Private::onTorrentFileError( QNetworkReply::NetworkError ) {
	QNetworkReply * reply = static_cast< QNetworkReply * >( this->sender() );
	QString message = reply->errorString();
	reply->deleteLater();
	emit this->error( QString( "can not fetch torrent because %1" ).arg( message ) );
}

void TorrentSession::Private::onTorrentFileSSLError( const QList< QSslError > & errors ) {
	QNetworkReply * reply = static_cast< QNetworkReply * >( this->sender() );
	reply->deleteLater();
	for( auto it = errors.begin(); it != errors.end(); ++it ) {
		emit this->error( it->errorString() );
	}
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
	QVariantList range = Settings::instance().get( "listen" ).toList();
	this->p_->session.listen_on( std::make_pair( range.first().toInt(), range.last().toInt() ) );
}

TorrentSession::~TorrentSession() {
}

void TorrentSession::addTorrent( const QByteArray & data ) {
	libtorrent::lazy_entry e;
	int ret = libtorrent::lazy_bdecode( data.data(), data.data() + data.size(), e );
	if( ret != 0 ) {
		throw TorrentException( "bdecode failed", __FILE__, __LINE__ );
	}
	libtorrent::add_torrent_params p;
	p.save_path = Settings::instance().get( "storage" ).toString().toStdString();
	p.ti = new libtorrent::torrent_info( e );
	libtorrent::torrent_handle th = this->p_->session.add_torrent( p );
}

// FIXME this method blocks MAIN thread
void TorrentSession::addTorrent( const QUrl & url ) {
	if( url.scheme() != "http" && url.scheme() != "https" ) {
		throw TorrentException( QString( "can not fetch torrent from %1" ).arg( url.toString() ), __FILE__, __LINE__ );
	}

	QNetworkRequest request( url );
	QNetworkReply * reply = this->p_->nam.get( request );
	this->p_->connect( reply, SIGNAL( finished() ), SLOT( onTorrentFileReady() ) );
	this->p_->connect( reply, SIGNAL( error( QNetworkReply::NetworkError ) ), SLOT( onTorrentFileError( QNetworkReply::NetworkError ) ) );
	this->p_->connect( reply, SIGNAL( sslErrors( const QList< QSslError > & ) ), SLOT( onTorrentFileSSLError( const QList< QSslError > & ) ) );
}

QVariantList TorrentSession::listTorrent() const {
	std::vector< libtorrent::torrent_handle > ths = this->p_->session.get_torrents();
	QVariantList l;
	for( auto it = ths.begin(); it != ths.end(); ++it ) {
		QVariantMap m;
		m.insert( "name", QString::fromStdString( it->name() ) );
		libtorrent::torrent_status status = it->status();
		m.insert( "progress", static_cast< double >( status.progress ) );
		m.insert( "info_hash", QString::fromStdString( it->info_hash().to_string() ) );
		l.append( m );
	}
	return l;
}

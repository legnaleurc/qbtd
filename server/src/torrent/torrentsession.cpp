#include "torrentsession_p.hpp"
#include "exception/torrentexception.hpp"
#include "qbtd/settings.hpp"

using qbtd::torrent::TorrentSession;
using qbtd::exception::TorrentException;
using qbtd::utility::Settings;

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

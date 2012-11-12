#include <libtorrent/alert.hpp>
#include <libtorrent/alert_types.hpp>

#include "torrentsession_p.hpp"
#include "exception/torrentexception.hpp"
#include "qbtd/settings.hpp"
#include "control/controlserver.hpp"

namespace {

struct AlertVisiter {
	void operator()( const libtorrent::block_finished_alert & a ) const {
		auto infoHash = QByteArray( a.handle.info_hash().to_string().c_str() ).toHex();
		auto progress = a.handle.status().progress;
		qbtd::control::ControlServer::instance().progressChanged( infoHash, progress );
	}
};

}

using qbtd::torrent::TorrentSession;
using qbtd::exception::TorrentException;
using qbtd::utility::Settings;

std::unique_ptr< TorrentSession, std::function< void ( TorrentSession * ) > > TorrentSession::Private::self;

void TorrentSession::Private::destory( TorrentSession * data ) {
	delete data;
}

TorrentSession::Private::Private():
session(),
timer() {
	using libtorrent::alert;
	this->session.set_alert_mask( alert::error_notification | alert::progress_notification );

	this->timer.setInterval( 3000 );
	this->connect( &this->timer, SIGNAL( timeout() ), SLOT( onBroadcastTimeout() ) );
}

void TorrentSession::Private::onBroadcastTimeout() {
	using libtorrent::alert;
	using libtorrent::handle_alert;
	using libtorrent::unhandled_alert;
	using libtorrent::block_finished_alert;
	AlertVisiter visiter;
	for( auto a = this->session.pop_alert(); a.get(); a = this->session.pop_alert() ) {
		auto msg = a->message();
		try {
			handle_alert< block_finished_alert >( a, visiter );
		} catch( unhandled_alert & ) {
			// ignore unhandled alert
		}
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
	this->p_->timer.start();
}

TorrentSession::~TorrentSession() {
}

QVariantMap TorrentSession::addTorrent( const QByteArray & data ) {
	libtorrent::lazy_entry e;
	int ret = libtorrent::lazy_bdecode( data.data(), data.data() + data.size(), e );
	if( ret != 0 ) {
		throw TorrentException( "bdecode failed", __FILE__, __LINE__ );
	}
	libtorrent::add_torrent_params p;
	p.save_path = Settings::instance().get( "storage" ).toString().toStdString();
	p.ti = new libtorrent::torrent_info( e );
	libtorrent::torrent_handle th = this->p_->session.add_torrent( p );
	libtorrent::torrent_status status = th.status();
	QVariantMap m;
	m.insert( "name", QString::fromStdString( th.name() ) );
	m.insert( "progress", static_cast< double >( status.progress ) );
	m.insert( "info_hash", QByteArray( th.info_hash().to_string().c_str() ).toHex() );
	return m;
}

QVariantList TorrentSession::listTorrent() const {
	std::vector< libtorrent::torrent_handle > ths = this->p_->session.get_torrents();
	QVariantList l;
	for( auto it = ths.begin(); it != ths.end(); ++it ) {
		QVariantMap m;
		m.insert( "name", QString::fromStdString( it->name() ) );
		libtorrent::torrent_status status = it->status();
		m.insert( "progress", static_cast< double >( status.progress ) );
		m.insert( "info_hash", QByteArray( it->info_hash().to_string().c_str() ).toHex() );
		l.append( m );
	}
	return l;
}

#include "commandhandler_p.hpp"
#include "torrent/torrentsession.hpp"
#include "exception/torrentexception.hpp"

#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QSslError>

#include <cassert>

using qbtd::control::CommandHandler;
using qbtd::exception::TorrentException;
using qbtd::torrent::TorrentSession;

CommandHandler::Private::Private():
QObject(),
commands(),
nam() {
	this->commands.insert( "add", std::bind( &Private::add, this, std::placeholders::_1 ) );
	this->commands.insert( "add_from_url", std::bind( &Private::addFromUrl, this, std::placeholders::_1 ) );
	this->commands.insert( "list", std::bind( &Private::list, this, std::placeholders::_1 ) );
}

std::pair< bool, QVariant > CommandHandler::Private::add( const QVariant & args ) {
	QByteArray data = QByteArray::fromBase64( args.toByteArray() );
	try {
		TorrentSession::instance().addTorrent( data );
		return std::make_pair( true, QVariant() );
	} catch( std::exception & e ) {
		return std::make_pair( false, QVariant( QString::fromUtf8( e.what() ) ) );
	}
}

std::pair< bool, QVariant > CommandHandler::Private::addFromUrl( const QVariant & args ) {
	QUrl url = args.toUrl();
	if( url.scheme() != "http" && url.scheme() != "https" && url.scheme() != "ftp" ) {
		return std::make_pair( false, QString( "can not fetch torrent from %1" ).arg( url.toString() ) );
	}
	this->loadFromUrl( url );
	return std::make_pair( true, QVariant() );
}

std::pair< bool, QVariant > CommandHandler::Private::list( const QVariant & /*args*/ ) {
	try {
		QVariant m = TorrentSession::instance().listTorrent();
		return std::make_pair( true, m );
	} catch( std::exception & e ) {
		return std::make_pair( false, QVariant( QString::fromUtf8( e.what() ) ) );
	}
}

void CommandHandler::Private::loadFromUrl( const QUrl & url ) {
	QNetworkRequest request( url );
	QNetworkReply * reply = this->nam.get( request );
	this->connect( reply, SIGNAL( finished() ), SLOT( onTorrentFileReady() ) );
	this->connect( reply, SIGNAL( error( QNetworkReply::NetworkError ) ), SLOT( onTorrentFileError( QNetworkReply::NetworkError ) ) );
	this->connect( reply, SIGNAL( sslErrors( const QList< QSslError > & ) ), SLOT( onTorrentFileSSLError( const QList< QSslError > & ) ) );
}

void CommandHandler::Private::onTorrentFileReady() {
	QNetworkReply * reply = static_cast< QNetworkReply * >( this->sender() );
	QByteArray torrent = reply->readAll();
	reply->deleteLater();
	try {
		TorrentSession::instance().addTorrent( torrent );
		emit this->broadcast( QString( "add" ), QString() );
	} catch( TorrentException & e ) {
		emit this->notify( QString( "warning" ), e.getMessage() );
	}
}

void CommandHandler::Private::onTorrentFileError( QNetworkReply::NetworkError ) {
	QNetworkReply * reply = static_cast< QNetworkReply * >( this->sender() );
	QString message = reply->errorString();
	reply->deleteLater();
	emit this->notify( QString( "warning" ), QString( "can not fetch torrent: %1" ).arg( message ) );
}

void CommandHandler::Private::onTorrentFileSSLError( const QList< QSslError > & errors ) {
	QNetworkReply * reply = static_cast< QNetworkReply * >( this->sender() );
	reply->deleteLater();
	for( auto it = errors.begin(); it != errors.end(); ++it ) {
		emit this->notify( QString( "warning" ), it->errorString() );
	}
}

CommandHandler::CommandHandler( QObject * parent ):
QObject( parent ),
p_( new Private ) {
	this->connect( this->p_.get(), SIGNAL( broadcast( const QString &, const QVariant & ) ), SIGNAL( broadcast( const QString &, const QVariant & ) ) );
	this->connect( this->p_.get(), SIGNAL( notify( const QString &, const QVariant & ) ), SIGNAL( notify( const QString &, const QVariant & ) ) );
}

std::pair< bool, QVariant > CommandHandler::execute( const QString & command, const QVariant & args ) const {
	auto it = this->p_->commands.find( command );
	if( it == this->p_->commands.end() ) {
		return std::make_pair( false, QObject::tr( "invalid command %1" ).arg( command ) );
	}
	return it.value()( args );
}

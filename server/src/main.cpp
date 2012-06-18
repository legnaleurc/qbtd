#include "torrent/torrentsession.hpp"
#include "control/controlserver.hpp"
#include "control/commandhandler.hpp"
#include "qbtd/settings.hpp"
#include "qbtd/exception.hpp"

#include <QtCore/QCoreApplication>
#include <QtCore/QTextCodec>
#include <QtCore/QRegExp>

#include <csignal>

void cleanup( int /*signum*/ ) {
	QCoreApplication::instance()->quit();
}

int main( int argc, char * argv[] ) {
	signal( SIGINT, cleanup );
	signal( SIGTERM, cleanup );
	signal( SIGABRT, cleanup );
#ifndef Q_OS_WIN
	signal( SIGQUIT, cleanup );
	signal( SIGHUP, cleanup );
#endif

	QCoreApplication a( argc, argv );

	QTextCodec::setCodecForCStrings( QTextCodec::codecForName( "UTF-8" ) );
	QTextCodec::setCodecForTr( QTextCodec::codecForName( "UTF-8" ) );

	using qbtd::utility::Settings;
	using qbtd::control::ControlServer;
	using qbtd::exception::Exception;

	try {
		Settings::initialize( "/tmp/qbtd.json" );
	} catch( Exception & e ) {
		QVariantList ctrl;
		ctrl.push_back( QString( "pipe:/tmp/qbtd.socket" ) );
		ctrl.push_back( QString( "localhost:9527" ) );

		QVariantMap settings;
		settings.insert( "control", ctrl );

		Settings::initialize( "/tmp/qbtd.json", settings );
	}
	qbtd::torrent::TorrentSession::initialize();
	qbtd::control::CommandHandler::initialize();
	ControlServer::initialize();

	QVariantList ctrls = Settings::instance().get( "control" ).toList();
	for( auto it = ctrls.begin(); it != ctrls.end(); ++it ) {
		QString socket = it->toString();
		QRegExp pipePattern( "^pipe:(.+)$" );
		QRegExp tcpPattern( "^(.+):(0|[1-9][0-9]*)$" );

		if( pipePattern.exactMatch( socket ) ) {
			socket = pipePattern.cap( 1 );
			if( !ControlServer::instance().listen( socket ) ) {
				a.exit( 1 );
			}
		} else if( tcpPattern.exactMatch( socket ) ) {
			QHostAddress address( tcpPattern.cap( 1 ) );
			quint16 port = tcpPattern.cap( 2 ).toUShort();
			if( !ControlServer::instance().listen( address, port ) ) {
				a.exit( 1 );
			}
		} else {
			// NOTE ignore invalid settings
		}
	}

	return a.exec();
}

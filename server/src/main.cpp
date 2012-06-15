#include <QtCore/QCoreApplication>
#include <QtCore/QTextCodec>

#include "torrent/torrentsession.hpp"
#include "control/controlserver.hpp"
#include "control/commandhandler.hpp"

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

	qbtd::torrent::TorrentSession::initialize();
	qbtd::control::CommandHandler::initialize();
	qbtd::control::ControlServer::initialize();

	if( !qbtd::control::ControlServer::instance().listen( "/tmp/qbtd.socket" ) ) {
		a.exit( 1 );
	}

	return a.exec();
}

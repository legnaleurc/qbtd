#include <QtCore/QCoreApplication>
#include <QtCore/QTextCodec>

#include "torrentsession.hpp"
#include "controlserver.hpp"
#include "commandhandler.hpp"

#include <csignal>

void cleanup( int /*signum*/ ) {
	QCoreApplication::instance()->quit();
}

int main( int argc, char * argv[] ) {
	signal( SIGHUP, cleanup );
	signal( SIGINT, cleanup );
	signal( SIGTERM, cleanup );
	signal( SIGQUIT, cleanup );
	signal( SIGABRT, cleanup );

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

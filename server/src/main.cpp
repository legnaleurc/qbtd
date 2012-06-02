#include <QtCore/QCoreApplication>

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

	QCoreApplication a( argc, argv );

	qbtd::torrent::TorrentSession::initialize();
	qbtd::control::CommandHandler::initialize();
	qbtd::control::ControlServer::initialize();

	if( !qbtd::control::ControlServer::instance().listen( "/tmp/qbtd.socket" ) ) {
		a.exit( 1 );
	}

	return a.exec();
}

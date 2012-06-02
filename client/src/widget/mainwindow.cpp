#include "mainwindow_p.hpp"

#include <QtCore/QUrl>

#include <QtCore/QtDebug>

using qbtd::widget::MainWindow;
using qbtd::control::ClientSession;

MainWindow::Private::Private( MainWindow * host ):
host( host ),
ui(),
serverDialog( new ServerDialog( host ) ),
session( new ClientSession( this ) ) {
	this->ui.setupUi( host );

	this->connect( this->ui.action_Connect_To_Server, SIGNAL( triggered() ), SLOT( onConnectToServer() ) );
	this->connect( this->session, SIGNAL( connected() ), SLOT( onConnected() ) );
}

void MainWindow::Private::onConnectToServer() {
	if( QDialog::Accepted != this->serverDialog->exec() ) {
		return;
	}
	QString lsp = this->serverDialog->getLocalServerPath();
	// TODO handle failure
	this->session->connectToServer( lsp );
}

void MainWindow::Private::onConnected() {
	this->connect( this->session, SIGNAL( responsed( bool, const QVariant & ) ), SLOT( onResponsed( bool, const QVariant & ) ) );
	this->session->request( "add", QUrl::fromLocalFile( "/tmp/test.torrent" ) );
}

void MainWindow::Private::onResponsed( bool result, const QVariant & data ) {
	qDebug() << __PRETTY_FUNCTION__ << result << data;
}

MainWindow::MainWindow():
QMainWindow(),
p_( new Private( this ) ) {
}

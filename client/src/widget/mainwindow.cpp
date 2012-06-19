#include "mainwindow_p.hpp"
#include "control/controlsession.hpp"

#include <QtCore/QUrl>
#include <QtGui/QMessageBox>

using qbtd::widget::MainWindow;
using qbtd::control::ControlSession;

MainWindow::Private::Private( MainWindow * owner ):
owner( owner ),
ui(),
serverDialog( new ServerDialog( owner ) ),
uploadDialog( new UploadDialog( owner ) ) {
	this->ui.setupUi( owner );

	this->toggleUI( false );

	this->connect( this->ui.action_Connect_To_Server, SIGNAL( triggered() ), SLOT( onConnectToServer() ) );
	this->connect( this->ui.action_Upload_Torrent, SIGNAL( triggered() ), SLOT( onUploadTorrent() ) );
	this->connect( &ControlSession::instance(), SIGNAL( connected() ), SLOT( onConnected() ) );
	this->connect( &ControlSession::instance(), SIGNAL( error( bool, const QString & ) ), SLOT( onError( bool, const QString & ) ) );
}

void MainWindow::Private::toggleUI( bool connected ) {
	this->ui.action_Connect_To_Server->setDisabled( connected );
	this->ui.action_Upload_Torrent->setEnabled( connected );
	if( connected ) {
		this->ui.torrentView->start();
	} else {
		this->ui.torrentView->stop();
	}
}

void MainWindow::Private::onConnectToServer() {
	if( QDialog::Accepted != this->serverDialog->exec() ) {
		return;
	}
	if( this->serverDialog->isLocal() ) {
		QString lsp = this->serverDialog->getLocalServerPath();
		// TODO handle failure
		ControlSession::instance().connectToServer( lsp );
	} else {
		QPair< QHostAddress, quint16 > host = this->serverDialog->getTCPIP();
		ControlSession::instance().connectToServer( host.first, host.second );
	}
}

void MainWindow::Private::onConnected() {
	this->toggleUI( true );
}

void MainWindow::Private::onError( bool stop, const QString & message ) {
	if( stop ) {
		ControlSession::instance().disconnectFromServer();
		this->toggleUI( false );
	}
	QMessageBox::warning( this->owner, QObject::tr( "Session Error" ), message );
}

void MainWindow::Private::onUploadTorrent() {
	if( QDialog::Accepted != this->uploadDialog->exec() ) {
		return;
	}
	if( this->uploadDialog->isRemote() ) {
		ControlSession::instance().request( "add_from_url", this->uploadDialog->getURL(), nullptr );
	} else {
		ControlSession::instance().request( "add", this->uploadDialog->getLocalFile(), nullptr );
	}
}

MainWindow::MainWindow():
QMainWindow(),
p_( new Private( this ) ) {
}

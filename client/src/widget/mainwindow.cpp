#include "mainwindow_p.hpp"

#include <QtCore/QUrl>
#include <QtGui/QMessageBox>

#include <QtCore/QtDebug>

using qbtd::widget::MainWindow;
using qbtd::control::ClientSession;

MainWindow::Private::Private( MainWindow * owner ):
owner( owner ),
ui(),
serverDialog( new ServerDialog( owner ) ),
session( new ClientSession( this ) ),
uploadDialog( new UploadDialog( owner ) ) {
	this->ui.setupUi( owner );

	this->toggleUI( false );

	this->connect( this->ui.action_Connect_To_Server, SIGNAL( triggered() ), SLOT( onConnectToServer() ) );
	this->connect( this->ui.action_Upload_Torrent, SIGNAL( triggered() ), SLOT( onUploadTorrent() ) );
	this->connect( this->session, SIGNAL( connected() ), SLOT( onConnected() ) );
	this->connect( this->session, SIGNAL( error( bool, const QString & ) ), SLOT( onError( bool, const QString & ) ) );
}

void MainWindow::Private::toggleUI( bool connected ) {
	this->ui.action_Connect_To_Server->setDisabled( connected );
	this->ui.action_Upload_Torrent->setEnabled( connected );
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
	this->toggleUI( true );
}

void MainWindow::Private::onError( bool stop, const QString & message ) {
	if( stop ) {
		this->session->close();
		this->toggleUI( false );
	}
	QMessageBox::warning( this->owner, QObject::tr( "Session Error" ), message );
}

void MainWindow::Private::onResponsed( bool result, const QVariant & data ) {
	qDebug() << __PRETTY_FUNCTION__ << result << data;
}

void MainWindow::Private::onUploadTorrent() {
	if( QDialog::Accepted != this->uploadDialog->exec() ) {
		return;
	}
	if( this->uploadDialog->isRemote() ) {
		this->session->request( "add_from_remote", this->uploadDialog->getURL() );
	} else {
		this->session->request( "add", this->uploadDialog->getLocalFile() );
	}
}

MainWindow::MainWindow():
QMainWindow(),
p_( new Private( this ) ) {
}

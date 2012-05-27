#include "mainwindow_p.hpp"

using qbtd::widget::MainWindow;
using qbtd::control::ControlSession;

MainWindow::Private::Private( MainWindow * host ):
host( host ),
ui(),
serverDialog( new ServerDialog( host ) ),
session( new ControlSession ) {
	this->ui.setupUi( host );

	this->connect( this->ui.action_Connect_To_Server, SIGNAL( triggered() ), SLOT( onConnectToServer() ) );
}

void MainWindow::Private::onConnectToServer() {
	if( QDialog::Accepted != this->serverDialog->exec() ) {
		return;
	}
	QString lsp = this->serverDialog->getLocalServerPath();
}

MainWindow::MainWindow():
QMainWindow(),
p_( new Private( this ) ) {
}

#include "mainwindow_p.hpp"

using qbtd::widget::MainWindow;

MainWindow::Private::Private( MainWindow * host ):
host( host ),
ui() {
	this->ui.setupUi( host );
}

MainWindow::MainWindow():
QMainWindow(),
p_( new Private( this ) ) {
}

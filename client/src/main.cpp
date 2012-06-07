#include <QtGui/QApplication>

#include "widget/mainwindow.hpp"
#include "control/controlsession.hpp"

int main( int argc, char * argv[] ) {
	QApplication a( argc, argv );
	qbtd::control::ControlSession::initialize();
	qbtd::widget::MainWindow window;
	window.show();
	return a.exec();
}

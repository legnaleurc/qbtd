#include <QtGui/QApplication>

#include "widget/mainwindow.hpp"

int main( int argc, char * argv[] ) {
	QApplication a( argc, argv );
	qbtd::widget::MainWindow window;
	window.show();
	return a.exec();
}

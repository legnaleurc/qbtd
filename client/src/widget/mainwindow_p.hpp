#ifndef QBTD_CLIENT_WIDGET_MAINWINDOW_HPP_
#define QBTD_CLIENT_WIDGET_MAINWINDOW_HPP_

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

namespace qbtd {
namespace widget {

class MainWindow::Private {
public:
	explicit Private( MainWindow * host );

	MainWindow * host;
	Ui::MainWindow ui;
};

}
}

#endif

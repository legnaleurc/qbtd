#ifndef QBTD_CLIENT_WIDGET_MAINWINDOW_HPP_
#define QBTD_CLIENT_WIDGET_MAINWINDOW_HPP_

#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "serverdialog.hpp"
#include "qbtd/clientsession.hpp"

namespace qbtd {
namespace widget {

class MainWindow::Private: public QObject {
	Q_OBJECT
public:
	explicit Private( MainWindow * host );

public slots:
	void onConnectToServer();
	void onConnected();
	void onResponsed( bool result, const QVariant & data );

public:
	MainWindow * host;
	Ui::MainWindow ui;
	ServerDialog * serverDialog;
	control::ClientSession * session;
};

}
}

#endif

#ifndef QBTD_CLIENT_WIDGET_MAINWINDOW_HPP_
#define QBTD_CLIENT_WIDGET_MAINWINDOW_HPP_

#include <functional>
#include <unordered_map>

#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "serverdialog.hpp"
#include "uploaddialog.hpp"

namespace qbtd {
namespace widget {

class MainWindow::Private: public QObject {
	Q_OBJECT
public:
	explicit Private( MainWindow * owner );

	void toggleUI( bool connected );

public slots:
	void onConnectToServer();
	void onConnected();
	void onError( bool stop, const QString & message );
	void onListed( const QList< qbtd::model::TorrentInfo > & torrents );
	void onUploadTorrent();

public:
	MainWindow * owner;
	Ui::MainWindow ui;
	ServerDialog * serverDialog;
	UploadDialog * uploadDialog;
};

}
}

#endif

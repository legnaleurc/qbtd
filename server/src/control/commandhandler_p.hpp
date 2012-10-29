#ifndef QBTD_CONTROL_COMMANDHANDLER_HPP_
#define QBTD_CONTROL_COMMANDHANDLER_HPP_

#include "commandhandler.hpp"

#include <QtCore/QHash>
#include <QtCore/QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include <functional>

namespace qbtd {
namespace control {

class CommandHandler::Private: public QObject {
	Q_OBJECT
public:
	Private();

	std::pair< bool, QVariant > add( const QVariant & args );
	std::pair< bool, QVariant > addFromUrl( const QVariant & args );
	std::pair< bool, QVariant > list( const QVariant & args );

	void loadFromUrl( const QUrl & url );

public slots:
	void onTorrentFileReady();
	void onTorrentFileError( QNetworkReply::NetworkError );
	void onTorrentFileSSLError( const QList< QSslError > & );

signals:
	void broadcast( const QString & event, const QVariant & data );
	void notify( const QString & event, const QVariant & data );

public:
	QHash< QString, std::function< std::pair< bool, QVariant > ( const QVariant & ) > > commands;
	QNetworkAccessManager nam;
};

}
}

#endif

#ifndef TORRENTSESSION_HPP_
#define TORRENTSESSION_HPP_

#include "torrentsession.hpp"

#include <QtNetwork/QNetworkReply>

#include <libtorrent/session.hpp>

namespace qbtd {
namespace torrent {

class TorrentSession::Private: public QObject {
	Q_OBJECT
public:
	static void destory( TorrentSession * );
	static std::unique_ptr< TorrentSession, std::function< void ( TorrentSession * ) > > self;

	Private();

public slots:
	void onTorrentFileReady();
	void onTorrentFileError( QNetworkReply::NetworkError );
	void onTorrentFileSSLError( const QList< QSslError > & );

signals:
	void error( const QString & );

public:
	libtorrent::session session;
	QNetworkAccessManager nam;
};

}
}

#endif

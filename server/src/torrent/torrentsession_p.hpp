#ifndef TORRENTSESSION_HPP_
#define TORRENTSESSION_HPP_

#include <libtorrent/session.hpp>
#include <QtCore/QTimer>

#include "torrentsession.hpp"

namespace qbtd {
namespace torrent {

class TorrentSession::Private: public QObject {
	Q_OBJECT
public:
	static void destory( TorrentSession * );
	static std::unique_ptr< TorrentSession, std::function< void ( TorrentSession * ) > > self;

	Private();

public slots:
	void onBroadcastTimeout();

public:
	libtorrent::session session;
	QTimer timer;
};

}
}

#endif

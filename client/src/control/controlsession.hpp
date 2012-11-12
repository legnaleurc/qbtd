#ifndef QBTD_CONTROL_CONTROLSESSION_HPP
#define QBTD_CONTROL_CONTROLSESSION_HPP

#include <QtCore/QObject>
#include <QtNetwork/QHostAddress>

#include <functional>
#include <memory>

namespace qbtd {
namespace model {
class TorrentInfo;
}
namespace control {

class ControlSession: public QObject {
	Q_OBJECT
public:
	static void initialize();
	static ControlSession & instance();

	void connectToServer( const QString & path );
	void connectToServer( const QHostAddress & address, quint16 port );
	void disconnectFromServer();

	int addTorrentFile( const QString & filePath );
	int addTorrentUrl( const QUrl & url );
	int list();

signals:
	void connected();
	void disconnected();
	void error( bool stop, const QString & message );

	void torrentAdded( const qbtd::model::TorrentInfo & torrent );
	void torrentFileAdded();
	void torrentUrlAdded();
	void listed( const QList< qbtd::model::TorrentInfo > & torrents );

private:
	ControlSession();
	ControlSession( const ControlSession & );
	ControlSession & operator =( const ControlSession & );
	virtual ~ControlSession();
	class Private;
	friend class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif

#ifndef QBTD_CONTROL_CONTROLSESSION_HPP_
#define QBTD_CONTROL_CONTROLSESSION_HPP_

#include "controlsession.hpp"
#include "qbtd/clientsession.hpp"

#include <QtCore/QReadWriteLock>

#include <unordered_map>

namespace qbtd {
namespace control {

class ControlSession::Private: public QObject {
	Q_OBJECT
public:
	typedef std::function< void ( bool, const QVariant & ) > ResponseCallback;
	typedef std::function< void ( const QVariant & ) > NotifyCallback;

	static std::unique_ptr< ControlSession, std::function< void ( ControlSession * ) > > self;
	static void destroy( ControlSession * data );

	Private();

	int request( const QString & command, const QVariant & args, ResponseCallback success );

public slots:
	void onNotified( const QString & event, const QVariant & data );
	void onResponsed( int id, bool result, const QVariant & data );

signals:
	void torrentAdded( const qbtd::model::TorrentInfo & torrent );

public:
	QReadWriteLock lock;
	ClientSession * session;
	std::unordered_map< int, ResponseCallback > responseHandlers;
	QHash< QString, NotifyCallback > notifyHandlers;
};

}
}

#endif

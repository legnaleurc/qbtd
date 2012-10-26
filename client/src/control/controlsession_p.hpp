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
	static std::unique_ptr< ControlSession, std::function< void ( ControlSession * ) > > self;
	static void destroy( ControlSession * data );

	Private();

public slots:
	void onResponsed( int id, bool result, const QVariant & data );

public:
	QReadWriteLock lock;
	ClientSession * session;
	std::unordered_map< int, SuccessCallback > handlers;
};

}
}

#endif

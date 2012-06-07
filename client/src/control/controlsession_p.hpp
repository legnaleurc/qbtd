#ifndef QBTD_CONTROL_CONTROLSESSION_HPP_
#define QBTD_CONTROL_CONTROLSESSION_HPP_

#include "controlsession.hpp"
#include "qbtd/clientsession.hpp"

namespace qbtd {
namespace control {

class ControlSession::Private: public QObject {
	Q_OBJECT
public:
	static std::unique_ptr< ControlSession, std::function< void ( ControlSession * ) > > self;
	static void destroy( ControlSession * data );

	Private();

public slots:
	void onResponsed( bool result, const QVariant & data );

public:
	ClientSession * session;
	SuccessCallback success;
};

}
}

#endif

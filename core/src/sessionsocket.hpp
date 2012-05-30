#ifndef QBTD_CONTROL_SESSIONSOCKET_HPP
#define QBTD_CONTROL_SESSIONSOCKET_HPP

#include <QtCore/QIODevice>

namespace qbtd {
namespace control {

class SessionSocket: public QIODevice {
	Q_OBJECT
protected:
	explicit SessionSocket( QObject * parent = 0 );

signals:
	void closed();
	void error( bool stop, const QString & message );
	void opened();
};

}
}

#endif

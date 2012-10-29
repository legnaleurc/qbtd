#ifndef QBTD_CONTROL_COMMANDHANDLER_HPP
#define QBTD_CONTROL_COMMANDHANDLER_HPP

#include <QtCore/QObject>
#include <QtCore/QVariant>

#include <memory>

namespace qbtd {
namespace control {

class CommandHandler: public QObject {
	Q_OBJECT
public:
	explicit CommandHandler( QObject * parent );

	std::pair< bool, QVariant > execute( const QString & command, const QVariant & args ) const;

signals:
	void notify( const QString & event, const QVariant & data );

private:
	class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif

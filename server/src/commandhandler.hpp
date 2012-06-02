#ifndef QBTD_CONTROL_COMMANDHANDLER_HPP
#define QBTD_CONTROL_COMMANDHANDLER_HPP

#include <QtCore/QVariant>

#include <memory>

namespace qbtd {
namespace control {

class CommandHandler {
public:
	static void initialize();
	static CommandHandler & instance();

	std::pair< bool, QVariant > execute( const QString & command, const QVariant & args ) const;

private:
	CommandHandler();
	~CommandHandler();
	CommandHandler( const CommandHandler & );
	CommandHandler & operator =( const CommandHandler & );
	class Private;
	friend class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif

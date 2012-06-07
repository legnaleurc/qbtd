#ifndef QBTD_CONTROL_COMMANDHANDLER_HPP_
#define QBTD_CONTROL_COMMANDHANDLER_HPP_

#include "commandhandler.hpp"

#include <QtCore/QHash>

namespace qbtd {
namespace control {

class CommandHandler::Private {
public:
	static std::unique_ptr< CommandHandler, std::function< void ( CommandHandler * ) > > self;
	static void destory( CommandHandler * );

	Private();

	std::pair< bool, QVariant > add( const QVariant & args );
	std::pair< bool, QVariant > list( const QVariant & args );

	QHash< QString, std::function< std::pair< bool, QVariant > ( const QVariant & ) > > commands;
};

}
}

#endif

#ifndef QBTD_CONTROL_COMMANDHANDLER_HPP_
#define QBTD_CONTROL_COMMANDHANDLER_HPP_

#include "commandhandler.hpp"

#include <QtCore/QHash>

#include <functional>

namespace qbtd {
namespace control {

class CommandHandler::Private {
public:
	Private();

	std::pair< bool, QVariant > add( const QVariant & args );
	std::pair< bool, QVariant > addFromUrl( const QVariant & args );
	std::pair< bool, QVariant > list( const QVariant & args );

	QHash< QString, std::function< std::pair< bool, QVariant > ( const QVariant & ) > > commands;
};

}
}

#endif

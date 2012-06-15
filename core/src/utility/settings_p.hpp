#ifndef QBTD_UTILITY_SETTINGS_HPP_
#define QBTD_UTILITY_SETTINGS_HPP_

#include "qbtd/settings.hpp"

#include <QtScript/QScriptEngine>

#include <functional>

namespace qbtd {
namespace utility {

class Settings::Private {
public:
	static std::unique_ptr< Settings, std::function< void ( Settings * ) > > self;
	static void destroy( Settings * data );

	Private( const QString & path );

	void save();

	QString path;
	QScriptEngine engine;
	QVariantMap data;
};

}
}

#endif

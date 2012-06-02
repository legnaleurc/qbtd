#ifndef QBTD_UTILITY_JSON_HPP
#define QBTD_UTILITY_JSON_HPP

#include <QtCore/QVariant>
#include <QtScript/QScriptEngine>

namespace qbtd {
namespace utility {

QVariant fromJSON( const QString & json, QScriptEngine * engine );
QString toJSON( const QVariant & variant, QScriptEngine * engine );

}
}

#endif

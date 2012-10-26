#include "json.hpp"
#include "qbtd/jsonerror.hpp"

#include <QtCore/QUrl>

namespace {

	QScriptValue serialize( const QVariant & value, QScriptEngine * engine ) {
		switch( value.type() ) {
		case QVariant::Map:
		{
			QScriptValue object = engine->newObject();
			QVariantMap map = value.toMap();
			for( auto it = map.begin(); it != map.end(); ++it ) {
				object.setProperty( it.key(), serialize( it.value(), engine ) );
			}
			return object;
		}
		case QVariant::List:
		{
			QVariantList list = value.toList();
			QScriptValue array = engine->newArray( list.size() );
			for( int i = 0; i < list.size(); ++i ) {
				array.setProperty( i, serialize( list.at( i ), engine ) );
			}
			return array;
		}
		case QVariant::String:
			return QScriptValue( value.toString() );
		case QVariant::Int:
			return QScriptValue( value.toInt() );
		case QVariant::UInt:
			return QScriptValue( value.toUInt() );
		case QVariant::Bool:
			return QScriptValue( value.toBool() );
		case QVariant::ByteArray:
			return QScriptValue( value.toByteArray().constData() );
		case QVariant::Double:
			return QScriptValue( value.toDouble() );
		case QVariant::Url:
			return QScriptValue( value.toUrl().toString() );
		default:
			return engine->nullValue();
		}
	}

}

namespace qbtd {
namespace utility {

QVariant fromJSON( const QString & json, QScriptEngine * engine ) {
	engine->globalObject().setProperty( "tmp", json );
	QScriptValue v = engine->evaluate( "JSON.parse( tmp );" );
	engine->globalObject().setProperty( "tmp", engine->nullValue() );
	if( engine->hasUncaughtException() ) {
		v = engine->uncaughtException();
		throw exception::JsonError( v.property( "message" ).toString(), __FILE__, __LINE__ );
	}
	return v.toVariant();
}

QString toJSON( const QVariant & variant, QScriptEngine * engine ) {
	engine->globalObject().setProperty( "tmp", serialize( variant, engine ) );
	QString json = engine->evaluate( "JSON.stringify( tmp );" ).toString();
	engine->globalObject().setProperty( "tmp", engine->nullValue() );
	if( engine->hasUncaughtException() ) {
		QScriptValue v = engine->uncaughtException();
		throw exception::JsonError( v.property( "message" ).toString(), __FILE__, __LINE__ );
	}
	return json;
}

QString toJSON( const QVariant & variant, const QString & spacer, QScriptEngine * engine ) {
	engine->globalObject().setProperty( "tmp", serialize( variant, engine ) );
	engine->globalObject().setProperty( "spacer", spacer );
	QString json = engine->evaluate( "JSON.stringify( tmp, null, spacer );" ).toString();
	engine->globalObject().setProperty( "spacer", engine->nullValue() );
	engine->globalObject().setProperty( "tmp", engine->nullValue() );
	if( engine->hasUncaughtException() ) {
		QScriptValue v = engine->uncaughtException();
		throw exception::JsonError( v.property( "message" ).toString(), __FILE__, __LINE__ );
	}
	return json;
}

}
}

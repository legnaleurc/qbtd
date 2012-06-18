#ifndef QBTD_UTILITY_SETTINGS_HPP
#define QBTD_UTILITY_SETTINGS_HPP

#include <QtCore/QString>
#include <QtCore/QVariant>

#include <memory>

namespace qbtd {
namespace utility {

class Settings {
public:
	static void initialize( const QString & path );
	static void initialize( const QString & path, const QVariantMap & settings );
	static Settings & instance();

	QVariant get( const QString & key ) const;
	void set( const QString & key, const QVariant & value );

private:
	Settings( const QString & );
	Settings( const Settings & );
	Settings & operator =( const Settings & );
	~Settings();
	class Private;
	friend class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif

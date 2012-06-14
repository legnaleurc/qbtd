#ifndef QBTD_EXCEPTION_EXCEPTION_HPP
#define QBTD_EXCEPTION_EXCEPTION_HPP

#include <exception>
#include <memory>

#include <QtCore/QString>

namespace qbtd {
namespace exception {

class Exception: public std::exception {
public:
	explicit Exception( int errnum );
	explicit Exception( const char * message );
	Exception( const char * message, std::size_t n );
	explicit Exception( const wchar_t * message );
	Exception( const wchar_t * message, std::size_t n );
	explicit Exception( const std::string & message );
	explicit Exception( const std::wstring & message );
	explicit Exception( const QString & message );
	virtual ~Exception() throw();

	virtual const char * what() const throw();
	const QString & getMessage() const;

private:
	class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif

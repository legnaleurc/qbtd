#ifndef QBTD_EXCEPTION_EXCEPTION_HPP
#define QBTD_EXCEPTION_EXCEPTION_HPP

#include <exception>
#include <memory>

#include <QtCore/QString>

namespace qbtd {
namespace exception {

class Exception: public std::exception {
public:
	explicit Exception( int errnum, const char * file, std::size_t line );
	explicit Exception( const char * message, const char * file, std::size_t line );
	Exception( const char * message, std::size_t n, const char * file, std::size_t line );
	explicit Exception( const wchar_t * message, const char * file, std::size_t line );
	Exception( const wchar_t * message, std::size_t n, const char * file, std::size_t line );
	explicit Exception( const std::string & message, const char * file, std::size_t line );
	explicit Exception( const std::wstring & message, const char * file, std::size_t line );
	explicit Exception( const QString & message, const char * file, std::size_t line );
	virtual ~Exception() throw();

	virtual const char * what() const throw();
	const QString & getMessage() const;
	const QString & getFile() const;
	std::size_t getLine() const;
	const QString & toString() const;

private:
	class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif

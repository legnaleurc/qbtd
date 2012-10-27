#ifndef QBTD_EXCEPTION_FILEERROR_HPP
#define QBTD_EXCEPTION_FILEERROR_HPP

#include "qbtd/exception.hpp"

namespace qbtd {
namespace exception {

class QBTD_DLL FileError: public Exception {
public:
	FileError( int errnum, const char * file, std::size_t line );
	FileError( const char * message, const char * file, std::size_t line );
	FileError( const char * message, std::size_t n, const char * file, std::size_t line );
	FileError( const wchar_t * message, const char * file, std::size_t line );
	FileError( const wchar_t * message, std::size_t n, const char * file, std::size_t line );
	FileError( const std::string & message, const char * file, std::size_t line );
	FileError( const std::wstring & message, const char * file, std::size_t line );
	FileError( const QString & message, const char * file, std::size_t line );
	virtual ~FileError() throw();
};

}
}

#endif

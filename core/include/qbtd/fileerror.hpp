#ifndef QBTD_EXCEPTION_FILEERROR_HPP
#define QBTD_EXCEPTION_FILEERROR_HPP

#include "qbtd/exception.hpp"

namespace qbtd {
namespace exception {

class FileError: public Exception {
public:
	explicit FileError( int errnum );
	explicit FileError( const char * message );
	FileError( const char * message, std::size_t n );
	explicit FileError( const wchar_t * message );
	FileError( const wchar_t * message, std::size_t n );
	explicit FileError( const std::string & message );
	explicit FileError( const std::wstring & message );
	explicit FileError( const QString & message );
	virtual ~FileError() throw();
};

}
}

#endif

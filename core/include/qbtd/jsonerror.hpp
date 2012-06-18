#ifndef QBTD_EXCEPTION_JSONERROR_HPP
#define QBTD_EXCEPTION_JSONERROR_HPP

#include "qbtd/exception.hpp"

namespace qbtd {
namespace exception {

class JsonError: public Exception {
public:
	explicit JsonError( int errnum );
	explicit JsonError( const char * message );
	JsonError( const char * message, std::size_t n );
	explicit JsonError( const wchar_t * message );
	JsonError( const wchar_t * message, std::size_t n );
	explicit JsonError( const std::string & message );
	explicit JsonError( const std::wstring & message );
	explicit JsonError( const QString & message );
	virtual ~JsonError() throw();
};

}
}

#endif

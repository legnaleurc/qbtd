#include "qbtd/jsonerror.hpp"

using qbtd::exception::JsonError;

JsonError::JsonError( int errnum, const char * file, std::size_t line ): Exception( errnum, file, line ) {
}

JsonError::JsonError( const char * message, const char * file, std::size_t line ): Exception( message, file, line ) {
}

JsonError::JsonError( const char * message, std::size_t n, const char * file, std::size_t line ): Exception( message, n, file, line ) {
}

JsonError::JsonError( const wchar_t * message, const char * file, std::size_t line ): Exception( message, file, line ) {
}

JsonError::JsonError( const wchar_t * message, std::size_t n, const char * file, std::size_t line ): Exception( message, n, file, line ) {
}

JsonError::JsonError( const std::string & message, const char * file, std::size_t line ): Exception( message, file, line ) {
}

JsonError::JsonError( const std::wstring & message, const char * file, std::size_t line ): Exception( message, file, line ) {
}

JsonError::JsonError( const QString & message, const char * file, std::size_t line ): Exception( message, file, line ) {
}

JsonError::~JsonError() throw() {
}

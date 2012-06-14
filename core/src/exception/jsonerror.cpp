#include "qbtd/jsonerror.hpp"

using qbtd::exception::JsonError;

JsonError::JsonError( int errnum ): Exception( errnum ) {
}

JsonError::JsonError( const char * message ): Exception( message ) {
}

JsonError::JsonError( const char * message, std::size_t n ): Exception( message, n ) {
}

JsonError::JsonError( const wchar_t * message ): Exception( message ) {
}

JsonError::JsonError( const wchar_t * message, std::size_t n ): Exception( message, n ) {
}

JsonError::JsonError( const std::string & message ): Exception( message ) {
}

JsonError::JsonError( const std::wstring & message ): Exception( message ) {
}

JsonError::JsonError( const QString & message ): Exception( message ) {
}

JsonError::~JsonError() throw() {
}

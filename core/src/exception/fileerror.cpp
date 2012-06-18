#include "qbtd/fileerror.hpp"

using qbtd::exception::FileError;

FileError::FileError( int errnum ): Exception( errnum ) {
}

FileError::FileError( const char * message ): Exception( message ) {
}

FileError::FileError( const char * message, std::size_t n ): Exception( message, n ) {
}

FileError::FileError( const wchar_t * message ): Exception( message ) {
}

FileError::FileError( const wchar_t * message, std::size_t n ): Exception( message, n ) {
}

FileError::FileError( const std::string & message ): Exception( message ) {
}

FileError::FileError( const std::wstring & message ): Exception( message ) {
}

FileError::FileError( const QString & message ): Exception( message ) {
}

FileError::~FileError() throw() {
}

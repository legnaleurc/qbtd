#include "qbtd/fileerror.hpp"

using qbtd::exception::FileError;

FileError::FileError( int errnum, const char * file, std::size_t line ): Exception( errnum, file, line ) {
}

FileError::FileError( const char * message, const char * file, std::size_t line ): Exception( message, file, line ) {
}

FileError::FileError( const char * message, std::size_t n, const char * file, std::size_t line ): Exception( message, n, file, line ) {
}

FileError::FileError( const wchar_t * message, const char * file, std::size_t line ): Exception( message, file, line ) {
}

FileError::FileError( const wchar_t * message, std::size_t n, const char * file, std::size_t line ): Exception( message, n, file, line ) {
}

FileError::FileError( const std::string & message, const char * file, std::size_t line ): Exception( message, file, line ) {
}

FileError::FileError( const std::wstring & message, const char * file, std::size_t line ): Exception( message, file, line ) {
}

FileError::FileError( const QString & message, const char * file, std::size_t line ): Exception( message, file, line ) {
}

FileError::~FileError() throw() {
}

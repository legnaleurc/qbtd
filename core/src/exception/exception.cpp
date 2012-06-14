#include "exception_p.hpp"

using qbtd::exception::Exception;

Exception::Private::Private( const QString & msg ): msg( msg ) {
}

Exception::Exception( int errnum ): std::exception(), p_( std::make_shared< Private >( QString::fromUtf8( strerror( errnum ) ) ) ) {
}

Exception::Exception( const char * message ): std::exception(), p_( std::make_shared< Private >( QString::fromUtf8( message ) ) ) {
}

Exception::Exception( const char * message, std::size_t n ): std::exception(), p_( std::make_shared< Private >( QString::fromUtf8( message, n ) ) ) {
}

Exception::Exception( const wchar_t * message ): std::exception(), p_( std::make_shared< Private >( QString::fromWCharArray( message ) ) ) {
}

Exception::Exception( const wchar_t * message, std::size_t n ): std::exception(), p_( std::make_shared< Private >( QString::fromWCharArray( message, n ) ) ) {
}

Exception::Exception( const std::string & message ): std::exception(), p_( std::make_shared< Private >( QString::fromUtf8( message.c_str() ) ) ) {
}

Exception::Exception( const std::wstring & message ): std::exception(), p_( std::make_shared< Private >( QString::fromStdWString( message ) ) ) {
}

Exception::Exception( const QString & message ): std::exception(), p_( std::make_shared< Private >( message ) ) {
}

Exception::~Exception() throw() {
}

const char * Exception::what() const throw() {
	return this->p_->msg.toLocal8Bit();
}

const QString & Exception::getMessage() const {
	return this->p_->msg;
}

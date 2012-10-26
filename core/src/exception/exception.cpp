#include "exception_p.hpp"

using qbtd::exception::Exception;

Exception::Private::Private( const QString & msg, const char * file, std::size_t line ):
msg( msg ),
file( QString::fromLocal8Bit( file ) ),
line( line ),
cachedString( QString( "%1 (%2::%3)" ).arg( msg ).arg( this->file ).arg( line ) ) {
}

Exception::Exception( int errnum, const char * file, std::size_t line ):
std::exception(),
p_( std::make_shared< Private >( QString::fromUtf8( strerror( errnum ) ), file, line ) ) {
}

Exception::Exception( const char * message, const char * file, std::size_t line ):
std::exception(),
p_( std::make_shared< Private >( QString::fromUtf8( message ), file, line ) ) {
}

Exception::Exception( const char * message, std::size_t n, const char * file, std::size_t line ):
std::exception(),
p_( std::make_shared< Private >( QString::fromUtf8( message, n ), file, line ) ) {
}

Exception::Exception( const wchar_t * message, const char * file, std::size_t line ):
std::exception(),
p_( std::make_shared< Private >( QString::fromWCharArray( message ), file, line ) ) {
}

Exception::Exception( const wchar_t * message, std::size_t n, const char * file, std::size_t line ):
std::exception(),
p_( std::make_shared< Private >( QString::fromWCharArray( message, n ), file, line ) ) {
}

Exception::Exception( const std::string & message, const char * file, std::size_t line ):
std::exception(),
p_( std::make_shared< Private >( QString::fromUtf8( message.c_str() ), file, line ) ) {
}

Exception::Exception( const std::wstring & message, const char * file, std::size_t line ):
std::exception(),
p_( std::make_shared< Private >( QString::fromStdWString( message ), file, line ) ) {
}

Exception::Exception( const QString & message, const char * file, std::size_t line ):
std::exception(),
p_( std::make_shared< Private >( message, file, line ) ) {
}

Exception::~Exception() throw() {
}

const char * Exception::what() const throw() {
	return this->p_->msg.toLocal8Bit();
}

const QString & Exception::getMessage() const {
	return this->p_->msg;
}

const QString & Exception::getFile() const {
	return this->p_->file;
}

std::size_t Exception::getLine() const {
	return this->p_->line;
}

const QString & Exception::toString() const {
	return this->p_->cachedString;
}

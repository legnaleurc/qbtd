#include "torrentexception.hpp"

using qbtd::exception::TorrentException;

TorrentException::TorrentException( int errnum, const char * file, std::size_t line ): Exception( errnum, file, line ) {
}

TorrentException::TorrentException( const char * message, const char * file, std::size_t line ): Exception( message, file, line ) {
}

TorrentException::TorrentException( const char * message, std::size_t n, const char * file, std::size_t line ): Exception( message, n, file, line ) {
}

TorrentException::TorrentException( const wchar_t * message, const char * file, std::size_t line ): Exception( message, file, line ) {
}

TorrentException::TorrentException( const wchar_t * message, std::size_t n, const char * file, std::size_t line ): Exception( message, n, file, line ) {
}

TorrentException::TorrentException( const std::string & message, const char * file, std::size_t line ): Exception( message, file, line ) {
}

TorrentException::TorrentException( const std::wstring & message, const char * file, std::size_t line ): Exception( message, file, line ) {
}

TorrentException::TorrentException( const QString & message, const char * file, std::size_t line ): Exception( message, file, line ) {
}

TorrentException::~TorrentException() throw() {
}

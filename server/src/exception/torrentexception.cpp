#include "torrentexception.hpp"

using qbtd::exception::TorrentException;

TorrentException::TorrentException( int errnum ): Exception( errnum ) {
}

TorrentException::TorrentException( const char * message ): Exception( message ) {
}

TorrentException::TorrentException( const char * message, std::size_t n ): Exception( message, n ) {
}

TorrentException::TorrentException( const wchar_t * message ): Exception( message ) {
}

TorrentException::TorrentException( const wchar_t * message, std::size_t n ): Exception( message, n ) {
}

TorrentException::TorrentException( const std::string & message ): Exception( message ) {
}

TorrentException::TorrentException( const std::wstring & message ): Exception( message ) {
}

TorrentException::TorrentException( const QString & message ): Exception( message ) {
}

TorrentException::~TorrentException() throw() {
}

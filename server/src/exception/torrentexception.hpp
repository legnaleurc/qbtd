#ifndef QBTD_EXCEPTION_TORRENTEXCEPTION_HPP
#define QBTD_EXCEPTION_TORRENTEXCEPTION_HPP

#include "qbtd/exception.hpp"

namespace qbtd {
namespace exception {

class TorrentException: public Exception {
public:
	explicit TorrentException( int errnum, const char * file, std::size_t line );
	explicit TorrentException( const char * message, const char * file, std::size_t line );
	TorrentException( const char * message, std::size_t n, const char * file, std::size_t line );
	explicit TorrentException( const wchar_t * message, const char * file, std::size_t line );
	TorrentException( const wchar_t * message, std::size_t n, const char * file, std::size_t line );
	explicit TorrentException( const std::string & message, const char * file, std::size_t line );
	explicit TorrentException( const std::wstring & message, const char * file, std::size_t line );
	explicit TorrentException( const QString & message, const char * file, std::size_t line );
	virtual ~TorrentException() throw();
};

}
}

#endif

#ifndef QBTD_EXCEPTION_TORRENTEXCEPTION_HPP
#define QBTD_EXCEPTION_TORRENTEXCEPTION_HPP

#include "qbtd/exception.hpp"

namespace qbtd {
namespace exception {

class TorrentException: public Exception {
public:
	explicit TorrentException( int errnum );
	explicit TorrentException( const char * message );
	TorrentException( const char * message, std::size_t n );
	explicit TorrentException( const wchar_t * message );
	TorrentException( const wchar_t * message, std::size_t n );
	explicit TorrentException( const std::string & message );
	explicit TorrentException( const std::wstring & message );
	explicit TorrentException( const QString & message );
	virtual ~TorrentException() throw();
};

}
}

#endif

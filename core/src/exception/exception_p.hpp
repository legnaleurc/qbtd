#ifndef QBTD_EXCEPTION_EXCEPTION_HPP_
#define QBTD_EXCEPTION_EXCEPTION_HPP_

#include "qbtd/exception.hpp"

namespace qbtd {
namespace exception {

class Exception::Private {
public:
	explicit Private( const QString & msg, const char * file, std::size_t line );

	QString msg;
	QString file;
	std::size_t line;
	QString cachedString;
};

}
}

#endif

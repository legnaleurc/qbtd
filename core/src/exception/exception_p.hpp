#ifndef QBTD_EXCEPTION_EXCEPTION_HPP_
#define QBTD_EXCEPTION_EXCEPTION_HPP_

#include "qbtd/exception.hpp"

namespace qbtd {
namespace exception {

class Exception::Private {
public:
	explicit Private( const QString & msg );

	QString msg;
};

}
}

#endif

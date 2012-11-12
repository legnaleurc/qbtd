#ifndef QBTD_MODEL_TORRENTINFO_HPP_
#define QBTD_MODEL_TORRENTINFO_HPP_

#include "torrentinfo.hpp"

namespace qbtd {
namespace model {

class TorrentInfo::Private {
public:
	Private( const QVariantMap & data );

	QByteArray infoHash;
	QString name;
	qreal progress;
};

}
}

#endif

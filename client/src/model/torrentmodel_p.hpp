#ifndef QBTD_MODEL_TORRENTMODEL_HPP_
#define QBTD_MODEL_TORRENTMODEL_HPP_

#include "torrentmodel.hpp"
#include "torrentinfo.hpp"

namespace qbtd {
namespace model {

class TorrentModel::Private {
public:
	Private();

	QList< TorrentInfo > torrents;
};

}
}

#endif

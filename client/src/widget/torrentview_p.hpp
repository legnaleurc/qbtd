#ifndef QBTD_WIDGET_TORRENTVIEW_HPP_
#define QBTD_WIDGET_TORRENTVIEW_HPP_

#include "torrentview.hpp"
#include "model/torrentmodel.hpp"

namespace qbtd {
namespace widget {

class TorrentView::Private {
public:
	explicit Private( TorrentView * owner );

public:
	TorrentView * owner;
	qbtd::model::TorrentModel * model;
};

}
}

#endif

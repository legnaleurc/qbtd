#ifndef QBTD_WIDGET_TORRENTVIEW_HPP
#define QBTD_WIDGET_TORRENTVIEW_HPP

#include <QtGui/QTreeView>

#include <memory>

namespace qbtd {
namespace model {
class TorrentInfo;
}
namespace widget {

class TorrentView: public QTreeView {
public:
	explicit TorrentView( QWidget * parent );

	void addTorrent( const qbtd::model::TorrentInfo & torrent );

private:
	class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif

#ifndef QBTD_WIDGET_TORRENTDELEGATE_HPP
#define QBTD_WIDGET_TORRENTDELEGATE_HPP

#include <QtGui/QStyledItemDelegate>

namespace qbtd {
namespace widget {

class TorrentDelegate: public QStyledItemDelegate {
public:
	explicit TorrentDelegate( QObject * parent = 0 );

	virtual void paint( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
};

}
}

#endif

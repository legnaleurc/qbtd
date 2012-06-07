#ifndef QBTD_WIDGET_TORRENTVIEW_HPP_
#define QBTD_WIDGET_TORRENTVIEW_HPP_

#include "torrentview.hpp"

#include <QtCore/QTimer>

namespace qbtd {
namespace widget {

class TorrentView::Private: public QObject {
	Q_OBJECT
public:
	Private( TorrentView * owner );

public slots:
	void onTimeout();

public:
	TorrentView * owner;
	QTimer * timer;
};

}
}

#endif

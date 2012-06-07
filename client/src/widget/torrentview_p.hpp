#ifndef QBTD_WIDGET_TORRENTVIEW_HPP_
#define QBTD_WIDGET_TORRENTVIEW_HPP_

#include "torrentview.hpp"

#include <QtCore/QTimer>
#include <QtGui/QStandardItemModel>

namespace qbtd {
namespace widget {

class TorrentView::Private: public QObject {
	Q_OBJECT
public:
	Private( TorrentView * owner );

	void doList( bool result, const QVariant & data );

public slots:
	void onTimeout();

public:
	TorrentView * owner;
	QTimer * timer;
	QStandardItemModel * model;
};

}
}

#endif

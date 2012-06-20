#include "torrentdelegate.hpp"

#include <QtGui/QPainter>
#include <QtGui/QStyleOptionProgressBarV2>
#include <QtGui/QApplication>

using qbtd::widget::TorrentDelegate;

TorrentDelegate::TorrentDelegate( QObject * parent ):
QStyledItemDelegate( parent ) {
}

void TorrentDelegate::paint( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const {
	if( index.column() != 1 ) {
		this->QStyledItemDelegate::paint( painter, option, index );
		return;
	}

	painter->save();

	double progress = index.data().toDouble();
	if( option.state & QStyle::State_Selected ) {
		painter->fillRect( option.rect, option.palette.highlight() );
	}
	QStyleOptionProgressBarV2 pb;
	pb.state = option.state;
	pb.direction = option.direction;
	pb.rect = option.rect;
	pb.fontMetrics = option.fontMetrics;
	pb.minimum = 0;
	pb.maximum = 100;
	pb.progress = progress * 100;
	pb.text = QString( "%1%%" ).arg( pb.progress );
	pb.textAlignment = Qt::AlignCenter;
	pb.textVisible = true;
	QApplication::style()->drawControl( QStyle::CE_ProgressBar, &pb, painter );

	painter->restore();
}

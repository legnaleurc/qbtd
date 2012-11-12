#include "torrentview_p.hpp"
#include "control/controlsession.hpp"
#include "torrentdelegate.hpp"

using qbtd::widget::TorrentView;
using qbtd::control::ControlSession;
using qbtd::widget::TorrentDelegate;
using qbtd::model::TorrentModel;

TorrentView::Private::Private( TorrentView * owner ):
owner( owner ),
model( new TorrentModel( owner ) ) {
	this->owner->setModel( this->model );
	this->owner->setItemDelegate( new TorrentDelegate( owner ) );
}

TorrentView::TorrentView( QWidget * parent ):
QTreeView( parent ),
p_( new Private( this ) ) {
}

void TorrentView::addTorrent( const qbtd::model::TorrentInfo & torrent ) {
	this->p_->model->addTorrent( torrent );
}

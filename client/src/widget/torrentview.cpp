#include "torrentview_p.hpp"
#include "control/controlsession.hpp"

using qbtd::widget::TorrentView;
using qbtd::control::ControlSession;

TorrentView::Private::Private( TorrentView * owner ):
QObject(),
owner( owner ),
timer( new QTimer( this ) ),
model( new QStandardItemModel( this ) ) {
	this->model->setColumnCount( 2 );
	this->owner->setModel( this->model );

	this->timer->setInterval( 5000 );

	this->connect( this->timer, SIGNAL( timeout() ), SLOT( onTimeout() ) );
}

void TorrentView::Private::onTimeout() {
	ControlSession::instance().request( "list", QVariant(), std::bind( &Private::doList, this, std::placeholders::_1, std::placeholders::_2 ) );
}

void TorrentView::Private::doList( bool result, const QVariant & data ) {
	if( !result ) {
		return;
	}
	QVariantList torrents = data.toList();
	this->model->setRowCount( torrents.size() );
	for( int i = 0; i < torrents.size(); ++i ) {
		QVariantMap torrent = torrents.at( i ).toMap();
		this->model->item( i, 0 )->setData( torrent.value( "name" ), Qt::DisplayRole );
		this->model->item( i, 1 )->setData( torrent.value( "progress" ), Qt::DisplayRole );
	}
}

TorrentView::TorrentView( QWidget * parent ):
QTreeView( parent ),
p_( new Private( this ) ) {
}

void TorrentView::start() {
	this->p_->timer->start();
}

void TorrentView::stop() {
	this->p_->timer->stop();
}

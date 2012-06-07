#include "torrentview_p.hpp"
#include "control/controlsession.hpp"

using qbtd::widget::TorrentView;
using qbtd::control::ControlSession;

TorrentView::Private::Private( TorrentView * owner ):
QObject(),
owner( owner ),
timer( new QTimer( this ) ) {
	this->timer->setInterval( 5000 );

	this->connect( this->timer, SIGNAL( timeout() ), SLOT( onTimeout() ) );
}

void TorrentView::Private::onTimeout() {
	ControlSession::instance().request( "list", QVariant(), nullptr );
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

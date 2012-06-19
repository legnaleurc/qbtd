#include "serverdialog_p.hpp"

using qbtd::widget::ServerDialog;

ServerDialog::Private::Private( ServerDialog * owner ):
owner( owner ),
ui(),
group( new QButtonGroup( owner ) ) {
	this->ui.setupUi( owner );

	this->group->setExclusive( true );
	this->group->addButton( this->ui.lsp, 0 );
	this->group->addButton( this->ui.tcpip, 1 );
}

ServerDialog::ServerDialog( QWidget * parent ):
QDialog( parent ),
p_( new Private( this ) ) {
}

bool ServerDialog::isLocal() const {
	return this->p_->group->checkedId() == 0;
}

QString ServerDialog::getLocalServerPath() const {
	return this->p_->ui.localServerPath->text();
}

QPair< QHostAddress, quint16 > ServerDialog::getTCPIP() const {
	QHostAddress address( this->p_->ui.address->text() );
	quint16 port = this->p_->ui.port->value();
	return qMakePair( address, port );
}

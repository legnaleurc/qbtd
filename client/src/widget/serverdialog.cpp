#include "serverdialog_p.hpp"

using qbtd::widget::ServerDialog;

ServerDialog::Private::Private( ServerDialog * host ):
host( host ),
ui() {
	this->ui.setupUi( host );
}

ServerDialog::ServerDialog( QWidget * parent ):
QDialog( parent ),
p_( new Private( this ) ) {
}

QString ServerDialog::getLocalServerPath() const {
	return this->p_->ui.localServerPath->text();
}

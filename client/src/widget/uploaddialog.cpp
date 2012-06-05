#include "uploaddialog_p.hpp"

#include <QtCore/QFile>

using qbtd::widget::UploadDialog;

UploadDialog::Private::Private( UploadDialog * owner ):
owner( owner ),
ui(),
group( new QButtonGroup( owner ) ) {
	this->ui.setupUi( owner );

	this->group->addButton( this->ui.fromLocal );
	this->group->addButton( this->ui.fromURL );
	this->group->setExclusive( true );
}

UploadDialog::UploadDialog( QWidget * parent ):
QDialog( parent ),
p_( new Private( this ) ) {
}

bool UploadDialog::isRemote() const {
	return this->p_->ui.fromLocal->isChecked();
}

QByteArray UploadDialog::getLocalFile() const {
	QFile fin( this->p_->ui.localFile->text() );
	if( !fin.open( QIODevice::ReadOnly ) ) {
		// TODO throw exception
		return QByteArray();
	}
	QByteArray data = fin.readAll();
	fin.close();
	data = data.toBase64();
	return data;
}

QUrl UploadDialog::getURL() const {
	return QUrl::fromUserInput( this->p_->ui.url->text() );
}

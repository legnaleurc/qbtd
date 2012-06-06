#include "uploaddialog_p.hpp"

#include <QtCore/QFile>
#include <QtGui/QFileDialog>

using qbtd::widget::UploadDialog;

UploadDialog::Private::Private( UploadDialog * owner ):
QObject(),
owner( owner ),
ui(),
group( new QButtonGroup( owner ) ) {
	this->ui.setupUi( owner );

	this->group->addButton( this->ui.fromLocal );
	this->group->addButton( this->ui.fromURL );
	this->group->setExclusive( true );

	this->connect( this->ui.browse, SIGNAL( clicked() ), SLOT( onBrowse() ) );
}

void UploadDialog::Private::onBrowse() {
	QString path = QFileDialog::getOpenFileName( this->owner, QObject::tr( "Upload Torrent" ), QDir::homePath() );
	if( path.isEmpty() ) {
		return;
	}
	this->ui.localFile->setText( path );
}

UploadDialog::UploadDialog( QWidget * parent ):
QDialog( parent ),
p_( new Private( this ) ) {
}

bool UploadDialog::isRemote() const {
	return this->p_->ui.fromURL->isChecked();
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

#ifndef QBTD_WIDGET_UPLOADDIALOG_HPP_
#define QBTD_WIDGET_UPLOADDIALOG_HPP_

#include "uploaddialog.hpp"
#include "ui_uploaddialog.h"

namespace qbtd {
namespace widget {

class UploadDialog::Private: public QObject {
	Q_OBJECT
public:
	Private( UploadDialog * owner );

public slots:
	void onBrowse();

public:
	UploadDialog * owner;
	Ui::UploadDialog ui;
	QButtonGroup * group;
};

}
}

#endif

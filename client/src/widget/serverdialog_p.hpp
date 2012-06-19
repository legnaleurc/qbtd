#ifndef QBTD_WIDGET_SERVERDIALOG_HPP_
#define QBTD_WIDGET_SERVERDIALOG_HPP_

#include "serverdialog.hpp"
#include "ui_serverdialog.h"

#include <QtGui/QButtonGroup>

namespace qbtd {
namespace widget {

class ServerDialog::Private {
public:
	explicit Private( ServerDialog * owner );

	ServerDialog * owner;
	Ui::ServerDialog ui;
	QButtonGroup * group;
};

}
}

#endif

#ifndef QBTD_WIDGET_SERVERDIALOG_HPP_
#define QBTD_WIDGET_SERVERDIALOG_HPP_

#include "serverdialog.hpp"
#include "ui_serverdialog.h"

namespace qbtd {
namespace widget {

class ServerDialog::Private {
public:
	explicit Private( ServerDialog * host );

	ServerDialog * host;
	Ui::ServerDialog ui;
};

}
}

#endif

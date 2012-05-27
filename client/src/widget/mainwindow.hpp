#ifndef QBTD_WIDGET_MAINWINDOW_HPP
#define QBTD_WIDGET_MAINWINDOW_HPP

#include <QtGui/QMainWindow>

#include <memory>

namespace qbtd {
namespace widget {

class MainWindow : public QMainWindow {
public:
	MainWindow();

private:
	class Private;
	std::shared_ptr< Private > p_;
};

}
}

#endif

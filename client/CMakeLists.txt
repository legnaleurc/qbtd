find_package(Qt4 REQUIRED QtNetwork)

include(${QT_USE_FILE})

set(QBTD_CLIENT_SOURCES "src/main.cpp" "src/widget/mainwindow.hpp" "src/widget/mainwindow_p.hpp" "src/widget/mainwindow.cpp" "src/widget/serverdialog.hpp" "src/widget/serverdialog_p.hpp" "src/widget/serverdialog.cpp")

qt4_wrap_cpp(QBTD_CLIENT_MOC_SOURCES "src/widget/mainwindow_p.hpp")
qt4_wrap_ui(QBTD_CLIENT_UIC_HEADERS "src/widget/mainwindow.ui" "src/widget/serverdialog.ui")

include_directories("${CMAKE_SOURCE_DIR}/core/include" ${CMAKE_CURRENT_BINARY_DIR})

add_executable(qbtd-client ${QBTD_CLIENT_SOURCES} ${QBTD_CLIENT_MOC_SOURCES} ${QBTD_CLIENT_UIC_HEADERS})
add_dependencies(qbtd-client qbtd-core)
target_link_libraries(qbtd-client qbtd-core ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTNETWORK_LIBRARY})
set_target_properties(qbtd-client PROPERTIES COMPILE_FLAGS "-std=c++0x -pipe -pedantic")

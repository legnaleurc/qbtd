find_package(Qt4 REQUIRED QtNetwork)

include(${QT_USE_FILE})

set(QBTD_CLIENT_SOURCES "src/main.cpp" "src/widget/mainwindow.hpp" "src/widget/mainwindow_p.hpp" "src/widget/mainwindow.cpp")

qt4_wrap_ui(QBTD_CLIENT_UIC_HEADERS "src/widget/mainwindow.ui")

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(qbtd-client ${QBTD_CLIENT_SOURCES} ${QBTD_CLIENT_MOC_SOURCES} ${QBTD_CLIENT_UIC_HEADERS})
target_link_libraries(qbtd-client ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTNETWORK_LIBRARY})
set_target_properties(qbtd-client PROPERTIES COMPILE_FLAGS "-std=c++0x -pipe -pedantic")

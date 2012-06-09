find_package(Qt4 REQUIRED QtNetwork)

include(${QT_USE_FILE})

set(QBTD_CLIENT_SOURCES "src/main.cpp" "src/widget/mainwindow.hpp" "src/widget/mainwindow_p.hpp" "src/widget/mainwindow.cpp" "src/widget/serverdialog.hpp" "src/widget/serverdialog_p.hpp" "src/widget/serverdialog.cpp" "src/widget/uploaddialog.hpp" "src/widget/uploaddialog_p.hpp" "src/widget/uploaddialog.cpp" "src/widget/torrentview.hpp" "src/widget/torrentview_p.hpp" "src/widget/torrentview.cpp" "src/control/controlsession.hpp" "src/control/controlsession_p.hpp" "src/control/controlsession.cpp")

qt4_wrap_cpp(QBTD_CLIENT_MOC_SOURCES "src/widget/mainwindow_p.hpp" "src/widget/uploaddialog_p.hpp" "src/widget/torrentview_p.hpp" "src/control/controlsession_p.hpp" "src/control/controlsession.hpp")
qt4_wrap_ui(QBTD_CLIENT_UIC_HEADERS "src/widget/mainwindow.ui" "src/widget/serverdialog.ui" "src/widget/uploaddialog.ui")

include_directories("${CMAKE_SOURCE_DIR}/core/include" "${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_executable(qbtd-client ${QBTD_CLIENT_SOURCES} ${QBTD_CLIENT_MOC_SOURCES} ${QBTD_CLIENT_UIC_HEADERS})
add_dependencies(qbtd-client qbtd-core)
target_link_libraries(qbtd-client qbtd-core ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTNETWORK_LIBRARY})
if(CMAKE_COMPILER_IS_GNUCXX)
	set_target_properties(qbtd-client PROPERTIES COMPILE_FLAGS "-std=c++0x -pipe -pedantic")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	# for clang; this detection is unstable, but close enough: http://www.cmake.org/cmake/help/cmake-2-8-docs.html#variable:CMAKE_LANG_COMPILER_ID
	set_target_properties(qbtd-client PROPERTIES COMPILE_FLAGS "-stdlib=libc++ -std=c++0x -pipe -pedantic" LINK_FLAGS "-stdlib=libc++")
endif()

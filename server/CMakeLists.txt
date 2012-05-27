find_package(Qt4 REQUIRED QtNetwork)
find_package(Boost REQUIRED system)
find_package(LibtorrentRasterbar REQUIRED)

include(${QT_USE_FILE})
include(${LIBTORRENT_RASTERBAR_USE_FILE})
include_directories(${BOOST_INCLUDE_DIRS})

set(QBTD_SOURCES "src/main.cpp" "src/inspector.hpp" "src/inspector.cpp" "src/torrentsession.hpp" "src/torrentsession_p.hpp" "src/torrentsession.cpp" "src/controlserver.hpp" "src/controlserver_p.hpp" "src/controlserver.cpp" "src/controlsession.hpp" "src/controlsession_p.hpp" "src/controlsession.cpp")

qt4_wrap_cpp(QBTD_MOC_SOURCES "src/inspector.hpp" "src/controlserver_p.hpp" "src/controlsession.hpp" "src/controlsession_p.hpp")

add_executable(qbtd-server ${QBTD_SOURCES} ${QBTD_MOC_SOURCES})
target_link_libraries(qbtd-server ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY} ${Boost_LIBRARIES} ${LIBTORRENT_RASTERBAR_LIBRARIES})
set_target_properties(qbtd-server PROPERTIES COMPILE_FLAGS "-std=c++0x -pipe -pedantic")

find_package(Qt4 REQUIRED QtNetwork)
find_package(Boost REQUIRED system)
find_package(LibtorrentRasterbar REQUIRED)

include(${QT_USE_FILE})
include(${LIBTORRENT_RASTERBAR_USE_FILE})
include_directories(${BOOST_INCLUDE_DIRS} "${CMAKE_SOURCE_DIR}/core/include")

set(QBTD_SERVER_SOURCES "src/main.cpp" "src/inspector.hpp" "src/inspector.cpp" "src/torrentsession.hpp" "src/torrentsession_p.hpp" "src/torrentsession.cpp" "src/controlserver.hpp" "src/controlserver_p.hpp" "src/controlserver.cpp")

qt4_wrap_cpp(QBTD_SERVER_MOC_SOURCES "src/inspector.hpp" "src/controlserver_p.hpp")

add_executable(qbtd-server ${QBTD_SERVER_SOURCES} ${QBTD_SERVER_MOC_SOURCES})
add_dependencies(qbtd-server qbtd-core)
target_link_libraries(qbtd-server qbtd-core ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY} ${Boost_LIBRARIES} ${LIBTORRENT_RASTERBAR_LIBRARIES})
set_target_properties(qbtd-server PROPERTIES COMPILE_FLAGS "-std=c++0x -pipe -pedantic")

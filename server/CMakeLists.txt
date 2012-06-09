find_package(Qt4 REQUIRED QtNetwork)
find_package(LibtorrentRasterbar REQUIRED)

include(${QT_USE_FILE})
include(${LIBTORRENT_RASTERBAR_USE_FILE})
include_directories("${CMAKE_SOURCE_DIR}/core/include")

set(QBTD_SERVER_SOURCES "src/main.cpp" "src/inspector.hpp" "src/inspector.cpp" "src/torrentsession.hpp" "src/torrentsession_p.hpp" "src/torrentsession.cpp" "src/controlserver.hpp" "src/controlserver_p.hpp" "src/controlserver.cpp" "src/commandhandler.hpp" "src/commandhandler_p.hpp" "src/commandhandler.cpp" "src/controlsession.hpp" "src/controlsession_p.hpp" "src/controlsession.cpp")

qt4_wrap_cpp(QBTD_SERVER_MOC_SOURCES "src/inspector.hpp" "src/controlserver_p.hpp" "src/controlsession.hpp" "src/controlsession_p.hpp")

add_executable(qbtd-server ${QBTD_SERVER_SOURCES} ${QBTD_SERVER_MOC_SOURCES})
add_dependencies(qbtd-server qbtd-core)
target_link_libraries(qbtd-server qbtd-core ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY} ${LIBTORRENT_RASTERBAR_LIBRARIES})
if(CMAKE_COMPILER_IS_GNUCXX)
	set_target_properties(qbtd-server PROPERTIES COMPILE_FLAGS "-std=c++0x -pipe -pedantic")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	# for clang; this detection is unstable, but close enough: http://www.cmake.org/cmake/help/cmake-2-8-docs.html#variable:CMAKE_LANG_COMPILER_ID
	set_target_properties(qbtd-server PROPERTIES COMPILE_FLAGS "-stdlib=libc++ -std=c++0x -pipe -pedantic" LINK_FLAGS "-stdlib=libc++")
endif()

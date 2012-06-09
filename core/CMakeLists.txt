find_package(Qt4 REQUIRED QtNetwork QtScript)

include(${QT_USE_FILE})

include_directories("include")
add_definitions(-DQBTD_LIBRARY)

set(QBTD_CORE_SOURCES "include/qbtd/config.hpp" "src/json.hpp" "src/json.cpp" "include/qbtd/clientsession.hpp" "src/clientsession_p.hpp" "src/clientsession.cpp" "include/qbtd/sessionserver.hpp" "src/sessionserver_p.hpp" "src/sessionserver.cpp" "include/qbtd/serversession.hpp" "src/serversession_p.hpp" "src/serversession.cpp" "src/sessionsocket.hpp" "src/sessionsocket_p.hpp" "src/sessionsocket.cpp" "src/localsessionsocket.hpp" "src/localsessionsocket_p.hpp" "src/localsessionsocket.cpp")

qt4_wrap_cpp(QBTD_CORE_MOC_SOURCES "include/qbtd/clientsession.hpp" "src/clientsession_p.hpp" "include/qbtd/sessionserver.hpp" "src/sessionserver_p.hpp" "include/qbtd/serversession.hpp" "src/serversession_p.hpp" "src/sessionsocket.hpp" "src/localsessionsocket_p.hpp")

add_library(qbtd-core SHARED ${QBTD_CORE_SOURCES} ${QBTD_CORE_MOC_SOURCES})
target_link_libraries(qbtd-core ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY} ${QT_QTSCRIPT_LIBRARY})
set_target_properties(qbtd-core PROPERTIES COMPILE_FLAGS "-std=c++0x -pipe -pedantic")
# for clang; this detection is unstable, but close enough: http://www.cmake.org/cmake/help/cmake-2-8-docs.html#variable:CMAKE_LANG_COMPILER_ID
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set_target_properties(qbtd-core PROPERTIES COMPILE_FLAGS "-stdlib=libc++ -std=c++0x -pipe -pedantic" LINK_FLAGS "-stdlib=libc++")
endif()

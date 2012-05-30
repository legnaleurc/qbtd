find_package(Qt4 REQUIRED QtNetwork QtScript)

include(${QT_USE_FILE})

include_directories("include")

set(QBTD_CORE_SOURCES "include/qbtd/clientsession.hpp" "src/clientsession_p.hpp" "src/clientsession.cpp" "include/qbtd/sessionserver.hpp" "src/sessionserver_p.hpp" "src/sessionserver.cpp" "include/qbtd/serversession.hpp" "src/serversession_p.hpp" "src/serversession.cpp" "src/sessionsocket.hpp" "src/sessionsocket_p.hpp" "src/sessionsocket.cpp" "src/localsessionsocket.hpp" "src/localsessionsocket_p.hpp" "src/localsessionsocket.cpp")

qt4_wrap_cpp(QBTD_CORE_MOC_SOURCES "include/qbtd/clientsession.hpp" "src/clientsession_p.hpp" "include/qbtd/sessionserver.hpp" "src/sessionserver_p.hpp" "include/qbtd/serversession.hpp" "src/serversession_p.hpp" "src/sessionsocket.hpp" "src/localsessionsocket_p.hpp")

add_library(qbtd-core SHARED ${QBTD_CORE_SOURCES} ${QBTD_CORE_MOC_SOURCES})
target_link_libraries(qbtd-core ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY} ${QT_QTSCRIPT_LIBRARY})
set_target_properties(qbtd-core PROPERTIES COMPILE_FLAGS "-std=c++0x -pipe -pedantic")

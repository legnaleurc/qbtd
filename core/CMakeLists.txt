find_package(Qt4 REQUIRED QtNetwork QtScript)

include(${QT_USE_FILE})

include_directories("include")

set(QBTD_CORE_SOURCES "include/qbtd/controlsession.hpp" "src/controlsession_p.hpp" "src/controlsession.cpp")

qt4_wrap_cpp(QBTD_CORE_MOC_SOURCES "include/qbtd/controlsession.hpp" "src/controlsession_p.hpp")

add_library(qbtd-core SHARED ${QBTD_CORE_SOURCES} ${QBTD_CORE_MOC_SOURCES})
target_link_libraries(qbtd-core ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY} ${QT_QTSCRIPT_LIBRARY})
set_target_properties(qbtd-core PROPERTIES COMPILE_FLAGS "-std=c++0x -pipe -pedantic")

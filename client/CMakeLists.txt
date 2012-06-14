find_package(Qt4 REQUIRED QtNetwork)

include(${QT_USE_FILE})

# glob all sources
file(GLOB_RECURSE QBTD_CLIENT_SOURCES "src/*.cpp")
file(GLOB_RECURSE QBTD_CLIENT_HEADERS "src/*.hpp")
file(GLOB_RECURSE QBTD_CLIENT_FORMS "src/*.ui")

set(QBTD_CLIENT_MOC_HEADERS "")
foreach(hdr ${QBTD_CLIENT_HEADERS})
	file(STRINGS "${hdr}" tmp REGEX "Q_OBJECT")
	if(tmp)
		list(APPEND QBTD_CLIENT_MOC_HEADERS "${hdr}")
	endif()
endforeach()

qt4_wrap_cpp(QBTD_CLIENT_MOC_SOURCES ${QBTD_CLIENT_MOC_HEADERS})
qt4_wrap_ui(QBTD_CLIENT_UIC_HEADERS ${QBTD_CLIENT_FORMS})

set(QBTD_CLIENT_COMPILE_UNITS ${QBTD_CLIENT_SOURCES} ${QBTD_CLIENT_HEADERS} ${QBTD_CLIENT_MOC_SOURCES} ${QBTD_CLIENT_FORMS})

include_directories("${CMAKE_SOURCE_DIR}/core/include" "${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_executable(qbtd-client ${QBTD_CLIENT_COMPILE_UNITS})
add_dependencies(qbtd-client qbtd-core)
target_link_libraries(qbtd-client qbtd-core ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTNETWORK_LIBRARY})
if(CMAKE_COMPILER_IS_GNUCXX)
	set_target_properties(qbtd-client PROPERTIES COMPILE_FLAGS "-std=c++0x -pipe -pedantic")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	# for clang; this detection is unstable, but close enough: http://www.cmake.org/cmake/help/cmake-2-8-docs.html#variable:CMAKE_LANG_COMPILER_ID
	set_target_properties(qbtd-client PROPERTIES COMPILE_FLAGS "-stdlib=libc++ -std=c++0x -pipe -pedantic" LINK_FLAGS "-stdlib=libc++")
endif()

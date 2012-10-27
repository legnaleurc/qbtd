find_package(Qt4 REQUIRED QtNetwork)
find_package(LibtorrentRasterbar REQUIRED)

include(${QT_USE_FILE})
include(${LIBTORRENT_RASTERBAR_USE_FILE})
include_directories("${CMAKE_SOURCE_DIR}/core/include" "${CMAKE_CURRENT_SOURCE_DIR}/src")

# glob all sources
file(GLOB_RECURSE QBTD_SERVER_SOURCES "src/*.cpp")
file(GLOB_RECURSE QBTD_SERVER_HEADERS "src/*.hpp")

set(QBTD_SERVER_MOC_HEADERS "")
foreach(hdr ${QBTD_SERVER_HEADERS})
	file(STRINGS "${hdr}" tmp REGEX "Q_OBJECT")
	if(tmp)
		list(APPEND QBTD_SERVER_MOC_HEADERS "${hdr}")
	endif()
endforeach()

qt4_wrap_cpp(QBTD_SERVER_MOC_SOURCES ${QBTD_SERVER_MOC_HEADERS})

set(QBTD_SERVER_COMPILE_UNITS ${QBTD_SERVER_SOURCES} ${QBTD_SERVER_HEADERS} ${QBTD_SERVER_MOC_SOURCES})

add_executable(qbtd-server ${QBTD_SERVER_COMPILE_UNITS})
add_dependencies(qbtd-server qbtd-core)
target_link_libraries(qbtd-server qbtd-core ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY} ${LIBTORRENT_RASTERBAR_LIBRARIES})
if(CMAKE_COMPILER_IS_GNUCXX)
	set_target_properties(qbtd-server PROPERTIES COMPILE_FLAGS "-std=c++0x -pipe -pedantic")
elseif(MSVC)
	set_target_properties(qbtd-server PROPERTIES COMPILE_FLAGS "/MP /Zc:wchar_t-")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	# for clang; this detection is unstable, but close enough: http://www.cmake.org/cmake/help/cmake-2-8-docs.html#variable:CMAKE_LANG_COMPILER_ID
	set_target_properties(qbtd-server PROPERTIES COMPILE_FLAGS "-stdlib=libc++ -std=c++0x -pipe -pedantic" LINK_FLAGS "-stdlib=libc++")
endif()

find_package(Qt4 REQUIRED QtNetwork QtScript)

include(${QT_USE_FILE})

include_directories("include" "src")
add_definitions(-DQBTD_LIBRARY)

# glob all sources
file(GLOB_RECURSE QBTD_CORE_SOURCES "src/*.cpp")
file(GLOB_RECURSE QBTD_CORE_HEADERS "src/*.hpp")
file(GLOB_RECURSE QBTD_CORE_PUBLIC_HEADERS "include/*.hpp")

set(QBTD_CORE_MOC_HEADERS "")
foreach(hdr ${QBTD_CORE_HEADERS} ${QBTD_CORE_PUBLIC_HEADERS})
	file(STRINGS "${hdr}" tmp REGEX "Q_OBJECT")
	if(tmp)
		list(APPEND QBTD_CORE_MOC_HEADERS "${hdr}")
	endif()
endforeach()

qt4_wrap_cpp(QBTD_CORE_MOC_SOURCES ${QBTD_CORE_MOC_HEADERS})

set(QBTD_CORE_COMPILE_UNITS ${QBTD_CORE_SOURCES} ${QBTD_CORE_HEADERS} ${QBTD_CORE_PUBLIC_HEADERS} ${QBTD_CORE_MOC_SOURCES})

add_library(qbtd-core SHARED ${QBTD_CORE_COMPILE_UNITS})
target_link_libraries(qbtd-core ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY} ${QT_QTSCRIPT_LIBRARY})
if(CMAKE_COMPILER_IS_GNUCXX)
	set_target_properties(qbtd-core PROPERTIES COMPILE_FLAGS "-std=c++0x -pipe -pedantic")
elseif(MSVC)
	set_target_properties(qbtd-core PROPERTIES COMPILE_FLAGS "/MP /Zc:wchar_t-")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	# for clang; this detection is unstable, but close enough: http://www.cmake.org/cmake/help/cmake-2-8-docs.html#variable:CMAKE_LANG_COMPILER_ID
	set_target_properties(qbtd-core PROPERTIES COMPILE_FLAGS "-stdlib=libc++ -std=c++0x -pipe -pedantic" LINK_FLAGS "-stdlib=libc++")
endif()

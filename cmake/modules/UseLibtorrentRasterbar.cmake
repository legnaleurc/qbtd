add_definitions(${LR_CFLAGS} ${LR_CFLAGS_OTHER})
if(MSVC)
	add_definitions(-DBOOST_ASIO_DYN_LINK -DBOOST_DATE_TIME_DYN_LINK -DBOOST_SYSTEM_DYN_LINK -DBOOST_THREAD_DYN_LINK)
endif()
include_directories(${Boost_INCLUDE_DIR} ${LIBTORRENT_RASTERBAR_INCLUDE_DIRS})

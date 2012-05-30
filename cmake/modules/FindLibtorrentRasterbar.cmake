find_package(PkgConfig)

if(PKG_CONFIG_FOUND AND NOT LibtorrentRasterbar_FOUND)
	pkg_check_modules(LR "libtorrent-rasterbar")
	if(LR_FOUND)
		set(LibtorrentRasterbar_FOUND ${LR_FOUND} CACHE INTERNAL "")
		set(LIBTORRENT_RASTERBAR_LIBRARIES ${LR_LIBRARIES} CACHE INTERNAL "")
		set(LIBTORRENT_RASTERBAR_LIBRARY_DIRS ${LR_LIBRARY_DIRS} CACHE INTERNAL "")
		set(LIBTORRENT_RASTERBAR_LDFLAGS ${LR_LDFLAGS} CACHE INTERNAL "")
		set(LIBTORRENT_RASTERBAR_LDFLAGS_OTHER ${LR_LDFLAGS_OTHER} CACHE INTERNAL "")
		set(LIBTORRENT_RASTERBAR_INCLUDE_DIRS ${LR_INCLUDE_DIRS} CACHE INTERNAL "")
	endif()
endif()

if(NOT LR_FOUND AND NOT LibtorrentRasterbar_FOUND)
	# find by my hand
	find_path(LR_INCLUDE_DIRS libtorrent)
	find_library(LR_LIBRARIES torrent-rasterbar)
	if(LR_INCLUDE_DIRS AND LR_LIBRARIES)
		set(LibtorrentRasterbar_FOUND TRUE CACHE INTERNAL "")
		set(LIBTORRENT_RASTERBAR_LIBRARIES ${LR_LIBRARIES} CACHE INTERNAL "")
		set(LIBTORRENT_RASTERBAR_LIBRARY_DIRS ${LR_LIBRARY_DIRS} CACHE INTERNAL "")
		set(LR_CFLAGS -DTORRENT_LINKING_SHARED -DTORRENT_USE_OPENSSL CACHE INTERNAL "")
		set(LR_CFLAGS_OTHER -DWITH_SHIPPED_GEOIP_H -DBOOST_ASIO_HASH_MAP_BUCKETS=1021 -DBOOST_FILESYSTEM_VERSION=2 CACHE INTERNAL "")
	endif()
endif()

set(LIBTORRENT_RASTERBAR_USE_FILE ${CMAKE_SOURCE_DIR}/cmake/modules/UseLibtorrentRasterbar.cmake)

if(LibtorrentRasterbar_FOUND)
else()
	if(LibtorrentRasterbar_FIND_REQUIRED)
		message(FATAL_ERROR "Could NOT find libtorrent-rasterbar")
	endif()
endif()

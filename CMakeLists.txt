# root
cmake_minimum_required(VERSION 2.6)

project(QBTD)

set(QBTD_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${QBTD_MODULE_PATH})

add_subdirectory("server")

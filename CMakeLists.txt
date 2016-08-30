cmake_minimum_required(VERSION 2.8)

project(sagtm)

set (CMAKE_CXX_FLAGS "-std=c++11 -Wall -g -Werror")
set (CMAKE_C_FLAGS "-Wall -g")

set (CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(src)
add_subdirectory(example)


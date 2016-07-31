cmake_minimum_required(VERSION 2.8)

project(sagtm)

set (CMAKE_CXX_FLAGS "-Wall -g")
set (CMAKE_C_FLAGS "-Wall -g")

add_subdirectory(src)
add_subdirectory(example)


link_directories(${CMAKE_BINARY_DIR}/bin)
include_directories(${CMAKE_SOURCE_DIR}/src)

add_subdirectory(client)
add_subdirectory(server)


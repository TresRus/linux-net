set (SERVER_H
    )

set (SERVER_CPP
    Server.cpp
    )

add_executable(server ${SERVER_CPP})
target_link_libraries(server linuxnet)


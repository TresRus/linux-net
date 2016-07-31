set (CLIENT_H
    )

set (CLIENT_CPP
    Client.cpp
    )

add_executable(client ${CLIENT_CPP})
target_link_libraries(client linuxnet)


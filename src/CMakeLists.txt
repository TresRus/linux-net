set (LINUX_NET_IFACE
    SocketTypes.h
    TcpClient.h
    TcpServer.h
    TcpSocket.h
    )

set (LINUX_NET_H
    ${LINUX_NET_IFACE}
    TcpInclude.h
    )

set (LINUX_NET_CPP
    TcpClient.cpp
    TcpServer.cpp
    TcpSocket.cpp
    )

add_library (linuxnet SHARED ${LINUX_NET_CPP})


set (LINUX_NET_IFACE
    SocketTypes.h
    TcpClient.h
    TcpServer.h
    TcpSocket.h
    )

set (LINUX_NET_H
    ${LINUX_NET_IFACE}
    SocketInclude.h
    Fd.h
    TcpBase.h
    TcpActive.h
    )

set (LINUX_NET_CPP
    TcpClient.cpp
    TcpServer.cpp
    TcpSocket.cpp
    Fd.cpp
    TcpBase.cpp
    TcpActive.cpp
    )

add_library (linuxnet SHARED ${LINUX_NET_CPP})


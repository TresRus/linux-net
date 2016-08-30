set (LINUX_NET_IFACE
    SocketTypes.h
    TcpClient.h
    TcpServer.h
    TcpActive.h
    TcpPassive.h
    )

set (LINUX_NET_H
    ${LINUX_NET_IFACE}
    SocketInclude.h
    Fd.h
    TcpBase.h
    )

set (LINUX_NET_CPP
    TcpClient.cpp
    TcpServer.cpp
    Fd.cpp
    TcpBase.cpp
    TcpActive.cpp
    TcpPassive.cpp
    )

add_library (linuxnet SHARED ${LINUX_NET_CPP})


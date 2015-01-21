#ifndef TCPSERVER_H_
#define TCPSERVER_H_

#include "TcpSocket.h"

namespace linuxnet {
namespace tcp {

typedef void (*ServerFun)(TcpSocket &sock);

class TcpServer
{
    ServerFun m_function;

public:
    TcpServer(ServerFun function);

    int run(int port);
};

}
}

#endif

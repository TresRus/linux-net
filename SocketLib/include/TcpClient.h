#ifndef TCPCLIENT_H_
#define TCPCLIENT_H_

#include "TcpSocket.h"
#include <string>

namespace linuxnet {
namespace tcp {

typedef void (*ClientFun)(TcpSocket &sock);

class TcpClient
{
    ClientFun m_function;

public:
    TcpClient(ClientFun function);

    int run(const std::string &addres, int port);
    int run_background(const std::string &addres, int port);
};

}
}

#endif

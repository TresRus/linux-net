#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include "TcpSocket.h"

namespace linuxnet {
namespace tcp {

////////////////////////////////////////////////////////////
// class Server

class Server
{
public:
    typedef void (function_type)(Socket &sock);

    Server(function_type *function);

    int run(int port);

private:
    function_type *m_function;

};

} // namespace tcp
} // namespace linuxnet

#endif // TCP_SERVER_H_


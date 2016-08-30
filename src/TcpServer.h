#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include "TcpActive.h"

namespace linuxnet {
namespace tcp {

////////////////////////////////////////////////////////////
// class Server

class Server
{
public:
    typedef void (function_type)(socket::tcp::ActiveSP);

    Server(function_type *function_);

    int run(int port_);

private:
    function_type *m_function;

};

} // namespace tcp
} // namespace linuxnet

#endif // TCP_SERVER_H_


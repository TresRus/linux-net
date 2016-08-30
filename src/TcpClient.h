#ifndef TCP_CLIENT_H_
#define TCP_CLIENT_H_

#include "TcpActive.h"
#include <string>

namespace linuxnet {
namespace tcp {

////////////////////////////////////////////////////////////
// class Client

class Client
{
public:
    typedef void (function_type)(socket::tcp::ActiveSP);

    Client(function_type *function_);

    int run(const std::string &addr_, int port_);
    int run_background(const std::string &addr_, int port_);

private:
    function_type *m_function;

};

} // namespace tcp
} // namespace linuxnet

#endif // TCP_CLIENT_H_


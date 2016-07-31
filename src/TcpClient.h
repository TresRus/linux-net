#ifndef TCP_CLIENT_H_
#define TCP_CLIENT_H_

#include "TcpSocket.h"
#include <string>

namespace linuxnet {
namespace tcp {

////////////////////////////////////////////////////////////
// class Client

class Client
{
public:
    typedef void (function_type)(Socket &sock);

    Client(function_type *function);

    int run(const std::string &addres, int port);
    int run_background(const std::string &addres, int port);

private:
    function_type *m_function;

};

} // namespace tcp
} // namespace linuxnet

#endif // TCP_CLIENT_H_


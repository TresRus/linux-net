#ifndef LINUX_NET_TCP_BASE_H_
#define LINUX_NET_TCP_BASE_H_

#include "Fd.h"
#include <string>

namespace linuxnet {
namespace socket {
namespace tcp {

////////////////////////////////////////////////////////////
// class Base

class Base
{
public:
    Base(FdSP fd_, const std::string &addr_, int port_);

    int fd() const;
    const std::string &addr() const;
    int port() const;

private:
    FdSP m_fd;
    std::string m_addr;
    int m_port;
};

} // namespace tcp
} // namespace socket
} // namespace linuxnet

#endif // LINUX_NET_TCP_BASE_H_


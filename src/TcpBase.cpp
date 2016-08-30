#include "TcpBase.h"
#include "SocketInclude.h"

namespace linuxnet {
namespace socket {
namespace tcp {

////////////////////////////////////////////////////////////
// class Base

Base::Base(FdSP fd_, const std::string &addr_, int port_):
    m_fd(fd_), m_addr(addr_), m_port(port_)
{
}

int Base::fd() const
{
    return m_fd->get();
}

const std::string &Base::addr() const
{
    return m_addr;
}

int Base::port() const
{
    return m_port;
}

} // namespace tcp
} // namespace socket
} // namespace linuxnet


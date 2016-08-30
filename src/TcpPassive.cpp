#include "TcpPassive.h"
#include "TcpBase.h"
#include "SocketInclude.h"
#include <iostream>

namespace linuxnet {
namespace socket {
namespace tcp {

const uint LISTENQ = 1024;

////////////////////////////////////////////////////////////
// class Passive

Passive::Passive(FdSP fd_, const std::string &addr_, int port_):
    m_base(new Base(fd_, addr_, port_))
{
}

ActiveSP Passive::accept()
{
    FdSP fd = Fd::accept(m_base->fd());
    if (fd == nullptr)
        return nullptr;

    return Active::accept(fd);
}

PassiveSP Passive::create(const std::string &addr_, int port_)
{
    FdSP fd = Fd::create();

    if (fd == nullptr)
        return nullptr;
    
    struct sockaddr_in sa;

    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port_);

    if (addr_.empty())
        sa.sin_addr.s_addr = htonl(INADDR_ANY);
    else if (inet_pton(AF_INET, addr_.c_str(), &sa.sin_addr) <= 0)
    {
        fprintf(stderr, "inet_pton error for %s\n", addr_.c_str());
        return nullptr;
    }

    if (::bind(fd->get(), (SA *) &sa, sizeof(sa)) < 0)
    {
        perror("bind");
        return nullptr;
    }

    if (::listen(fd->get(), LISTENQ) < 0)
    {
        perror("listen");
        return nullptr;
    }

    std::string a;
    int p;

    if (!fd->getLocalInfo(a, p))
        return nullptr;

    std::cout << "Create passive socket " << a << ":" << p << std::endl;

    return PassiveSP(new Passive(fd, a, p));
}

PassiveSP Passive::create(const std::string &addr_)
{
    return create(addr_, INADDR_ANY);
}

PassiveSP Passive::create(int port_)
{
    return create("", port_);
}

} // namespace tcp
} // namespace socket
} // namespace linuxnet



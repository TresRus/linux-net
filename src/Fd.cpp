#include "Fd.h"
#include "SocketInclude.h"

namespace linuxnet {
namespace socket {

////////////////////////////////////////////////////////////
// class Fd

Fd::Fd(int fd_):
    m_fd(fd_)
{
}

Fd::~Fd()
{
    ::close(m_fd);
}

bool Fd::getLocalInfo(std::string &addr_, int &port_)
{
    struct sockaddr_in sa;
    memset(&sa, 0, sizeof(sa));
    socklen_t l = sizeof(sa);

    getsockname(get(), (SA *) &sa, &l);

    char a[64];

    if (NULL == inet_ntop(sa.sin_family,
        &sa.sin_addr, a, sizeof(a)))
    {
        return false;
    }

    addr_ = a;
    port_ = ntohs(sa.sin_port);
    return true;
}

bool Fd::getRemoteInfo(std::string &addr_, int &port_)
{
    struct sockaddr_in sa;
    memset(&sa, 0, sizeof(sa));
    socklen_t l = sizeof(sa);

    getpeername(get(), (SA *) &sa, &l);

    char a[64];

    if (NULL == inet_ntop(sa.sin_family,
        &sa.sin_addr, a, sizeof(a)))
    {
        return false;
    }

    addr_ = a;
    port_ = ntohs(sa.sin_port);
    return true;
}

int Fd::get() const
{
    return m_fd;
}

FdSP Fd::create()
{
    int fd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("socket");
        return nullptr;
    }

    return FdSP(new Fd(fd));
}

FdSP Fd::accept(int fd_)
{
    int fd = ::accept(fd_, (SA *) NULL, NULL);
    if (fd < 0)
    {
        perror("accept");
        return nullptr;
    }

    return FdSP(new Fd(fd));
}


} // namespace socket
} // namespace linuxnet


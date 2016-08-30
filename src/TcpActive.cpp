#include "TcpActive.h"
#include "Fd.h"
#include "TcpBase.h"
#include "SocketInclude.h"
#include <iostream>

namespace linuxnet {
namespace socket {
namespace tcp {

////////////////////////////////////////////////////////////
// class Active

Active::Active(FdSP fd_, const std::string &addr_, int port_) :
    m_base(new Base(fd_, addr_, port_))
{
}

ssize_t Active::write(const byte *data_, size_t size_)
{
    ssize_t sended = 0;

    while (size_ > 0)
    {
        if ((sended = ::write(m_base->fd(), data_, size_)) <= 0)
        {
            if (errno == EINTR)
                sended = 0;
            else
                return -1;
        }
        size_ -= sended;
        data_ += sended;
    }

    return size_;
}

ssize_t Active::read(byte *data_, size_t size_)
{
    size_t free = size_;
    ssize_t readed = 0;

    while (free > 0)
    {
        if ((readed = ::read(m_base->fd(), data_, free)) < 0)
            return -1;
        else if(readed == 0)
            break;

        free -= readed;
        data_ += readed;
    }

    return size_ - free;
}

ssize_t Active::readTillByte(byte end_, byte *data_, size_t size_)
{
    size_t current;
    ssize_t rv;

    for (current = 1; current < size_; ++current)
    {
        byte b = 0;
        if ((rv = ::read(m_base->fd(), &b, 1)) < 0)
        {
            return -1;
        }

        *data_++ = b;

        if (rv == 0)
            return current-1;

        if (b == end_)
            break;
    }

    *data_++ = 0;
    return current;
}

ActiveSP Active::create(const std::string &remoteAddr_, int remoteIp_)
{
    FdSP fd = Fd::create();

    if (fd == nullptr)
        return nullptr;
    
    struct sockaddr_in sa;
    memset(&sa, 0, sizeof(sa));

    sa.sin_family = AF_INET;
    sa.sin_port = htons(remoteIp_);

    if (inet_pton(AF_INET, remoteAddr_.c_str(), &sa.sin_addr) <= 0)
    {
        fprintf(stderr, "inet_pton error for %s\n", remoteAddr_.c_str());
        return nullptr;
    }

    if (::connect(fd->get(), (SA *) &sa, sizeof(sa)) < 0)
    {
        perror("connect");
        return nullptr;
    } 

    std::string a;
    int p;

    if (!fd->getLocalInfo(a, p))
        return nullptr;

    std::cout << "Create active socket " << a << ":" << p << std::endl;

    return ActiveSP(new Active(fd, a, p));
}

ActiveSP Active::accept(FdSP fd_)
{
    std::string a;
    int p;

    if (!fd_->getRemoteInfo(a, p))
        return nullptr;

    std::cout << "Accept active socket " << a << ":" << p << std::endl;

    return ActiveSP(new Active(fd_, a, p));
}

} // namespace tcp
} // namespace socket
} // namespace linuxnet


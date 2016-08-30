#ifndef LINUX_NET_TCP_ACTIVE_H
#define LINUX_NET_TCP_ACTIVE_H

#include <memory>
#include "SocketTypes.h"

namespace linuxnet {
namespace socket {

class Fd;
typedef std::shared_ptr<Fd> FdSP;

namespace tcp {

class Base;
class Active;

typedef std::shared_ptr<Base> BaseSP;
typedef std::shared_ptr<Active> ActiveSP;

////////////////////////////////////////////////////////////
// class Active

class Active
{
public:
    ssize_t write(const byte *data_, size_t size_);
    ssize_t read(byte *data_, size_t size_);
    ssize_t readTillByte(byte end_, byte *data_, size_t size_);

    static ActiveSP create(const std::string &remoteAddr_, int remoteIp_);

    static ActiveSP accept(FdSP fd_);

private:
    Active(FdSP fd_, const std::string &addr_, int port_);

    const BaseSP m_base;
};

} // namespace tcp
} // namespace socket
} // namespace linuxnet

#endif // LINUX_NET_TCP_ACTIVE_H


#ifndef LINUX_NET_TCP_PASSIVE_H_
#define LINUX_NET_TCP_PASSIVE_H_

#include "TcpActive.h"
#include <memory>

namespace linuxnet {
namespace socket {

class Fd;
typedef std::shared_ptr<Fd> FdSP;

namespace tcp {

class Base;
class Passive;

typedef std::shared_ptr<Base> BaseSP;
typedef std::shared_ptr<Passive> PassiveSP;

////////////////////////////////////////////////////////////
// class Passive

class Passive
{
public:
    ActiveSP accept();

    static PassiveSP create(const std::string &addr_, int port_);
    static PassiveSP create(const std::string &addr_);
    static PassiveSP create(int port_);

private:
    Passive(FdSP fd_, const std::string &addr_, int port_);

    const BaseSP m_base;
};

} // namespace tcp
} // namespace socket
} // namespace linuxnet

#endif // LINUX_NET_TCP_PASSIVE_H_


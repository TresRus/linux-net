#ifndef LINUX_NET_FD_H_
#define LINUX_NET_FD_H_

#include <memory>

namespace linuxnet {
namespace socket {

class Fd;
typedef std::shared_ptr<Fd> FdSP;

////////////////////////////////////////////////////////////
// class Fd

class Fd
{
public:
    ~Fd();

    bool getLocalInfo(std::string &addr_, int &port_);
    bool getRemoteInfo(std::string &addr_, int &port_);

    int get() const;

    static FdSP create();
    static FdSP accept(int fd_);

private:
    Fd(int fd_);

    int m_fd;
};

} // namespace socket
} // namespace linuxnet

#endif // LINUX_NET_FD_H_


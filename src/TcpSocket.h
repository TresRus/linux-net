#ifndef TCP_SOCKET_H_
#define TCP_SOCKET_H_

#include <string>
#include "SocketTypes.h"

namespace linuxnet {
namespace tcp {

////////////////////////////////////////////////////////////
// class Socket

class Socket
{
public:
    Socket();
    ~Socket();

    bool bind(const std::string &ip, int port);
    bool bind(const std::string &ip);
    bool bind(int port);

    bool connect(const std::string &ip, int port);
    bool listen();
    Socket *accept();

    ssize_t write(const byte *data, size_t size);
    ssize_t read (byte *data, size_t size);
    ssize_t read_till_byte(byte end, byte *data, size_t size);

    void close();

    std::string getAddress();
    int getPort();

private:
    int m_fd;
    bool m_open;
    std::string m_address;
    int m_port;

    void localAddrPort();
    void remoteAddrPort(int fd, std::string &address, int &port);

    Socket(int fd, const std::string &address, int port);

};

} // namespace tcp
} // namespace linuxnet

#endif // TCP_SOCKET_H_


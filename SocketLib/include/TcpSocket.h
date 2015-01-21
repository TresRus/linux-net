#ifndef TCPSOCKET_H_
#define TCPSOCKET_H_

#include <string>
#include "SocketTypes.h"

namespace linuxnet {
namespace tcp {

const uint TCP_READ_BUFFER_SIZE = 1024;

class TcpSocket
{
private:
    int m_fd;
    bool m_open;

    int port;
    std::string address;

    void localAddrPort();
    void remoteAddrPort(int fd, std::string &addr, int &p);

    TcpSocket(int fd, const std::string &addr, int p);

public:
    TcpSocket();

    ~TcpSocket();

    bool bind(const std::string &ip, int port);
    bool bind(const std::string &ip);
    bool bind(int port);

    bool connect(const std::string &ip, int port);
    bool listen();
    TcpSocket *accept();

    ssize_t write(const byte *data, size_t size);
    ssize_t read (byte *data, size_t size);
    ssize_t read_till_byte(byte end, byte *data, size_t size);

    void close();

    std::string getAddress();
    int getPort();
};

}
}

#endif /* TCPSOCKET_H_ */

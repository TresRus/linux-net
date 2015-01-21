#include "include/TcpSocket.h"

#include <memory>
#include "SocketInclude.h"

namespace linuxnet {
namespace tcp {

const uint LISTENQ = 1024;

void TcpSocket::localAddrPort()
{
    struct sockaddr_in servaddr;

    memset(&servaddr, 0, sizeof(servaddr));
    socklen_t len = sizeof(servaddr);

    getsockname(m_fd, (SA *) &servaddr, &len);

    char addr[64];

    if(inet_ntop(servaddr.sin_family, &servaddr.sin_addr, addr, sizeof(addr)))

    address = addr;
    port = ntohs(servaddr.sin_port);
}

void TcpSocket::remoteAddrPort(int fd, std::string &addr, int &p)
{
    struct sockaddr_in servaddr;

    memset(&servaddr, 0, sizeof(servaddr));
    socklen_t len = sizeof(servaddr);

    getpeername(fd, (SA *) &servaddr, &len);

    char a[64];

    if(inet_ntop(servaddr.sin_family, &servaddr.sin_addr, a, sizeof(a)))

    addr = a;
    p = ntohs(servaddr.sin_port);
}

TcpSocket::TcpSocket(int fd, const std::string &addr, int p)
{
   m_fd = fd;
   m_open = true;
   address = addr;
   port = p;
}

TcpSocket::TcpSocket() :
        port(0),
        address("unknown")
{
   if( (m_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
   {
       perror("socket");
       m_open = false;
   }
   else
   {
       m_open = true;
   }
}

TcpSocket::~TcpSocket()
{
    if(m_open)
    {
        ::close(m_fd);
    }
}

bool TcpSocket::bind(const std::string &ip, int port)
{
    struct sockaddr_in servaddr;

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);

    if( inet_pton(AF_INET, ip.c_str(), &servaddr.sin_addr) <= 0)
    {
        fprintf(stderr, "inet_pton error for %s\n", ip.c_str());
        return false;
    }

    if( ::bind(m_fd, (SA *) &servaddr, sizeof(servaddr)) < 0 )
    {
        perror("bind");
        return false;
    }
    localAddrPort();
    return true;
}

bool TcpSocket::bind(const std::string &ip)
{
    struct sockaddr_in servaddr;

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(INADDR_ANY);

    if( inet_pton(AF_INET, ip.c_str(), &servaddr.sin_addr) <= 0)
    {
        fprintf(stderr, "inet_pton error for %s\n", ip.c_str());
        return false;
    }

    if( ::bind(m_fd, (SA *) &servaddr, sizeof(servaddr)) < 0 )
    {
        perror("bind");
        return false;
    }
    localAddrPort();
    return true;
}

bool TcpSocket::bind(int port)
{
    struct sockaddr_in servaddr;

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    if( ::bind(m_fd, (SA *) &servaddr, sizeof(servaddr)) < 0 )
    {
        perror("bind");
        return false;
    }
    localAddrPort();
    return true;
}

bool TcpSocket::connect(const std::string &ip, int port)
{
    struct sockaddr_in servaddr;

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);

    if( inet_pton(AF_INET, ip.c_str(), &servaddr.sin_addr) <= 0)
    {
        fprintf(stderr, "inet_pton error for %s\n", ip.c_str());
        return false;
    }

    if(::connect(m_fd, (SA *) &servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        return false;
    }
    localAddrPort();
    return true;
}

bool TcpSocket::listen()
{
    if( ::listen(m_fd, LISTENQ) < 0 )
    {
        perror("listen");
        return false;
    }
    localAddrPort();
    return true;
}

TcpSocket *TcpSocket::accept()
{
    int fd;
    if( (fd = ::accept(m_fd, (SA *) NULL, NULL)) < 0 )
    {
        perror("accept");
        return 0;
    }
    std::string addr;
    int p;

    remoteAddrPort(fd, addr, p);

    return new TcpSocket(fd, addr, p);
}

ssize_t TcpSocket::write(const byte *data, size_t size)
{
    if(!m_open)
        return -1;

    size_t left_to_send = size;
    ssize_t sended = 0;
    const byte *next = data;

    while(left_to_send > 0)
    {
        if( (sended = ::write(m_fd, next, left_to_send)) <= 0 )
        {
            if( errno == EINTR )
                sended = 0;
            else
                return -1;
        }
        left_to_send -= sended;
        next += sended;
    }
    return size;
}

ssize_t TcpSocket::read(byte *data, size_t size)
{
    if(!m_open)
        return -1;

    size_t left_to_read = size;
    ssize_t readed = 0;
    byte *next = data;

    while(left_to_read > 0)
    {
        if( (readed = ::read(m_fd, next, left_to_read)) < 0 )
        {
            return -1;
        }
        else if(readed == 0)
            break;

        left_to_read -= readed;
        next += readed;
    }
    return size - left_to_read;
}

ssize_t TcpSocket::read_till_byte(byte end, byte *data, size_t size)
{
    if(!m_open)
        return -1;

    byte *next = data;
    size_t   current;
    ssize_t  rv;

    for(current = 1; current < size; ++current)
    {
        byte b = 0;
        if( (rv = ::read(m_fd, &b, 1)) < 0 )
        {
            return -1;
        }

        *next++ = b;

        if(rv == 0)
            return current-1;

        if(b == end)
            break;
    }

    *next++ = 0;
    return current;
}

void TcpSocket::close()
{
    if(m_open)
    {
        m_open = false;
        ::close(m_fd);
    }
}

std::string TcpSocket::getAddress()
{
    return address;
}

int TcpSocket::getPort()
{
    return port;
}

}
}

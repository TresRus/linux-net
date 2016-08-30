#include "TcpClient.h"
#include "SocketInclude.h"
#include <iostream>

namespace linuxnet {
namespace tcp {
namespace client {

void signal_child_handler(int signo)
{
    pid_t pid;
    int stat;

    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
        std::cout << "Client fork " << pid << " terminate" << std::endl;

    return;
}

} // namespace client

////////////////////////////////////////////////////////////
// class Client

Client::Client(Client::function_type *function_) :
    m_function(function_)
{
}

int Client::run(const std::string &addr_, int port_)
{
    socket::tcp::ActiveSP sock =
        socket::tcp::Active::create(addr_, port_);

    if (sock == nullptr)
        return 1;

    std::cout << "Client" << std::endl;

    m_function(sock);

    return 0;
}

int Client::run_background(const std::string &addr_, int port_)
{
    signal(SIGCHLD, client::signal_child_handler);

    socket::tcp::ActiveSP sock =
        socket::tcp::Active::create(addr_, port_);
    
    if (sock == nullptr)
        return 1;

    std::cout << "Background client" << std::endl;

    int fr = fork();
    if (fr == -1)
    {
        perror("fork");
        return 1;
    }
    else if (fr == 0)
        m_function(sock);

    return 0;
}

} // namespace tcp
} // namespace linuxnet


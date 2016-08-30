#include "TcpServer.h"
#include "TcpPassive.h"
#include "SocketInclude.h"
#include <iostream>

namespace linuxnet {
namespace tcp {
namespace server {

void signal_child_handler(int signo)
{
    pid_t pid;
    int stat;

    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
        std::cout << "Client fork " << pid << " terminate" << std::endl;

    return;
}

} // namespace server

////////////////////////////////////////////////////////////
// class Server

Server::Server(Server::function_type function_) :
    m_function(function_)
{
}

int Server::run(int port_)
{
    signal(SIGCHLD, server::signal_child_handler);

    socket::tcp::PassiveSP sock = socket::tcp::Passive::create(port_);

    if (sock == nullptr)
        return 1;

    std::cout << "Server" << std::endl;

    for (;;)
    {
        std::cout << "Wait connection" << std::endl;
        socket::tcp::ActiveSP connected = sock->accept();

        if (connected == nullptr)
            return 1;

        std::cout << "Connected" << std::endl;

        int fr = fork();
        if (fr == -1)
        {
            perror("fork");
            return 1;
        }
        if (fr == 0)
        {
            sock.reset();

            m_function(connected);

            return 0;
        }
    }
    return 0;
}

} // namespace tcp
} // namespace linuxnet


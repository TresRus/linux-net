#include "TcpServer.h"
#include "SocketInclude.h"

namespace linuxnet {
namespace tcp {
namespace server {

void signal_child_handler(int signo)
{
    pid_t pid;
    int stat;

    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
        printf("Server fork %d terminate\n", pid);

    return;
}

} // namespace server

////////////////////////////////////////////////////////////
// class Server

Server::Server(Server::function_type function) :
    m_function(function)
{
}

int Server::run(int port)
{
    Socket sock;
    signal(SIGCHLD, server::signal_child_handler);

    if (!sock.bind(port))
            return 1;

    if (!sock.listen())
        return 1;

    printf("Server at %s:%d\n",
            sock.getAddress().c_str(), sock.getPort());

    for (;;)
    {
        printf("Wait connection\n");
        Socket *connected = sock.accept();

        if (connected == NULL)
            return 1;

        printf("Connected %s:%d\n",
               connected->getAddress().c_str(), connected->getPort());

        int fr = fork();
        if (fr == -1)
        {
            perror("fork");
            return 1;
        }
        if (fr == 0)
        {
            sock.close();

            m_function(*connected);

            delete connected;
            return 0;
        }
        delete connected;
    }
    return 0;
}

} // namespace tcp
} // namespace linuxnet


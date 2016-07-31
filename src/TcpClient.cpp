#include "TcpClient.h"
#include "SocketInclude.h"

namespace linuxnet {
namespace tcp {
namespace client {

void signal_child_handler(int signo)
{
    pid_t pid;
    int stat;

    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
        printf("Client fork %d terminate\n", pid);

    return;
}

} // namespace client

////////////////////////////////////////////////////////////
// class Client

Client::Client(Client::function_type *function) :
    m_function(function)
{
}

int Client::run(const std::string &addres, int port)
{
    Socket sock;

    sock.connect(addres, port);

    printf("Client at %s:%d\n",
        sock.getAddress().c_str(), sock.getPort());

    m_function(sock);

    return 0;
}

int Client::run_background(const std::string &addres, int port)
{
    Socket sock;

    signal(SIGCHLD, client::signal_child_handler);

    sock.connect(addres, port);

    printf("Background client at %s:%d\n",
        sock.getAddress().c_str(), sock.getPort());

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


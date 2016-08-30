#include "TcpActive.h"
#include "TcpServer.h"
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

const int MAXLINE = 128;

using namespace linuxnet;

void server_fun(socket::tcp::ActiveSP sock)
{
    int readed;
    char line[MAXLINE];

    while ( (readed = sock->readTillByte('\n', (byte *)line, sizeof(line))) )
    {
        sock->write((byte *)line, strlen(line));
    }
}

int main(int argc, char **argv)
{
    tcp::Server server(server_fun);

    if (argc != 2)
    {
        std::cout << "usage: server <Port>" << std::endl;
        return 1;
    }

    return server.run(atoi(argv[1]));
}


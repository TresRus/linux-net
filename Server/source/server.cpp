#include "TcpServer.h"
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

const int MAXLINE = 128;

using namespace linuxnet::tcp;

void server_fun(TcpSocket &sock)
{
    int readed;
    char line[MAXLINE];

    while( (readed = sock.read_till_byte('\n', (byte *)line, sizeof(line))) )
    {
        sock.write((byte *)line, strlen(line));
    }
}

int main(int argc, char **argv)
{
    TcpServer server(server_fun);

    if(argc != 2)
    {
        std::cout << "usage: server <Port>" << std::endl;
        return 1;
    }

    return server.run(atoi(argv[1]));
}

#include "TcpClient.h"
#include "SocketTypes.h"
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

const int MAXLINE = 128;

using namespace linuxnet::tcp;

void client_fun(TcpSocket &sock)
{
    char line[MAXLINE] = "";
    ssize_t readed;

    std::cin >> line;

    while(!strcmp(line, "q"))
    {
        strcat(line, "\n");

        sock.write((byte *)line, strlen(line));

        if( (readed = sock.read_till_byte('\n', (byte *)line, sizeof(line))) )
        {
            line[readed] = 0;
            std::cout << readed << std::endl;
        }
        std::cout << line;

        std::cin >> line;
    }
}

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        std::cout << "usage: client <IP> <Port>" << std::endl;
        return 1;
    }

    TcpClient client(client_fun);

    client.run(argv[1], atoi(argv[2]));
}

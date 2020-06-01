#include <iostream>
#include "endpoint/ServerEndpoint.h"

int main()
{
    ServerEndpoint server((Port()), "/mnt/mynfs", "root", "hosts.txt");
    std::cout << "Running server at " << server.getAddress().toString() << std::endl;
    server.run();

    return 0;
}
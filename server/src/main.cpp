#include <iostream>
#include "endpoint/ServerEndpoint.h"

int main()
{
    try
    {
        ServerEndpoint server((Port()), ".", "root", "hosts.txt");
        std::cout << "Running server at " << server.getAddress().toString() << std::endl;
        server.run();
    }
    catch (std::exception& e)
    {
        std::cout << "Unexpected exception. " + std::string(e.what()) << std::endl;
    }

    return 0;
}
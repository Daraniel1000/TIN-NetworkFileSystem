#include "endpoint/ServerEndpoint.h"

int main()
{
    ServerEndpoint server((Port()));
    server.run();

    return 0;
}
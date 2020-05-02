#include <iostream>
#include <messages/RequestMessage.h>
#include "socket/Socket.h"

int main()
{
    Socket socket((Port()));
    RequestMessage requestMessage(socket.receive(IpAddress("XD")));
    std::cout << "Hello World!" << requestMessage.getType();
    return 0;
}
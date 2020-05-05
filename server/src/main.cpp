#include <iostream>
#include <session/messages/RequestMessage.h>
#include <transport/socket/Socket.h>

int main()
{
    Socket socket((Port()));
    RequestMessage requestMessage(socket.receive());
    std::cout << "Hello World!" << requestMessage.getType();
    return 0;
}
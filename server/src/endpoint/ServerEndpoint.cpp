#include <session/messages/RequestMessage.h>
#include <addresses/EphemeralPort.h>
#include "ServerEndpoint.h"
#include "ServerSubEndpoint.h"


ServerEndpoint::ServerEndpoint(Port port) : socket(port) {}

void ServerEndpoint::run()
{
    NetworkAddress source;
    RequestMessage request(socket.receive(source));

    //run new thread here and go back to receiving on socket
    ServerSubEndpoint subEndpoint(Socket(EphemeralPort()), source, this->handlerFactoryPool);
    subEndpoint.run();
}

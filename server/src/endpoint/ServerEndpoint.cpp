#include <session/messages/RequestMessage.h>
#include <addresses/EphemeralPort.h>
#include <thread>
#include "ServerEndpoint.h"
#include "ServerSubEndpoint.h"


ServerEndpoint::ServerEndpoint(Port port) : socket(port) {}

void ServerEndpoint::run()
{
    NetworkAddress source;
    RequestMessage request(socket.receive(source));

    //run new thread here and go back to receiving on socket
    ServerSubEndpoint subEndpoint(Socket(EphemeralPort()), source, this->handlerFactoryPool, this->messageQueue);
    std::thread thread(&ServerSubEndpoint::run, &subEndpoint);  //TODO wrzucić to jeszcze w jakiś wektor czy coś jak to ma być w pętli
}

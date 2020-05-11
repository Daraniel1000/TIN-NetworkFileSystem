#include <session/messages/ConfirmMessage.h>
#include <session/messages/DataMessage.h>
#include "ServerSubEndpoint.h"

ServerSubEndpoint::ServerSubEndpoint(Socket socket, NetworkAddress clientAddress,
                                     const HandlerFactoryPool &handlerFactoryPool) : socket(socket),
                                                                                     clientAddress(clientAddress),
                                                                                     handlerFactoryPool(
                                                                                             handlerFactoryPool)
{

}

void ServerSubEndpoint::run()
{
    this->socket.send(clientAddress, ConfirmMessage().serialize());
    DataMessage requestDataMessage(this->socket.receive(clientAddress));

    const HandlerFactory &handlerFactory = handlerFactoryPool.getHandlerFactory(0/*requestDataMessage.getType()*/);

    DomainData replyData;
    auto handler = handlerFactory.create(requestDataMessage.getData(), replyData);

    //add handler to queue and wait for handling
    handler->handle();

    DataMessage replyDataMessage(requestDataMessage.getType(), replyData);

    this->socket.send(clientAddress, replyDataMessage.serialize());
    ConfirmMessage confirm(this->socket.receive(clientAddress));
}

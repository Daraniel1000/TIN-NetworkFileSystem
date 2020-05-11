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
    int8_t replyError = 0;
    auto handler = handlerFactory.create(requestDataMessage.getData(), replyData, replyError);

    //add handler to queue and wait for handling
    handler->handle();

    DataMessage replyDataMessage(requestDataMessage.getType(), replyData, replyError);

    this->socket.send(clientAddress, replyDataMessage.serialize());
    ConfirmMessage confirm(this->socket.receive(clientAddress));
}

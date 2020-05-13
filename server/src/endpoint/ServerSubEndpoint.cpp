#include <session/messages/ConfirmMessage.h>
#include <session/messages/DataMessage.h>
#include <mutex>
#include "ServerSubEndpoint.h"

ServerSubEndpoint::ServerSubEndpoint(UDPSocket socket, NetworkAddress clientAddress,
                                     const HandlerFactoryPool &handlerFactoryPool,
                                     SafeQueue<Handler*>& queueRef) : socket(socket), clientAddress(clientAddress),
                                                                handlerFactoryPool(handlerFactoryPool),
                                                                messageQueue(queueRef)
{

}

void ServerSubEndpoint::run()
{
    this->socket.send(clientAddress, ConfirmMessage().serialize());
    DataMessage requestDataMessage(this->socket.receive(clientAddress));

    const HandlerFactory &handlerFactory = handlerFactoryPool.getHandlerFactory(0/*requestDataMessage.getType()*/);

    DomainData replyData;
    int8_t replyError = 0;
    std::mutex requestFinished;
    auto handler = handlerFactory.create(requestDataMessage.getData(), replyData, replyError);

    //add handler to queue and wait for handling
    messageQueue.pushSafe(handler.get());
    std::unique_lock<std::mutex> lk(handler->m);
    handler->cv.wait(lk);   //wait_for żeby ustawić timeout wykonania

    DataMessage replyDataMessage(requestDataMessage.getType(), replyData, replyError);

    this->socket.send(clientAddress, replyDataMessage.serialize());
    ConfirmMessage confirm(this->socket.receive(clientAddress));
}

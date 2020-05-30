#include <session/messages/ConfirmMessage.h>
#include <session/messages/DataMessage.h>
#include <mutex>
#include <iostream>
#include "ServerSubEndpoint.h"

ServerSubEndpoint::ServerSubEndpoint(NetworkAddress clientAddress,
                                     const HandlerFactoryPool &handlerFactoryPool,
                                     SafeQueue<Handler*>& queueRef,
                                     ThreadCounter& counterRef,
                                     Port port) : socket(port),
                                                  clientAddress(clientAddress),
                                                  handlerFactoryPool(handlerFactoryPool),
                                                  messageQueue(queueRef),
                                                  counter(counterRef)
{

}

void ServerSubEndpoint::run()
{
    this->socket.send(clientAddress, ConfirmMessage().serialize());
    DataMessage requestDataMessage(this->socket.receive(clientAddress));

    const HandlerFactory &handlerFactory = handlerFactoryPool.getHandlerFactory(requestDataMessage.getType());

    DomainData replyData;
    PlainError replyError;
    std::mutex requestFinished;
    auto handler = handlerFactory.create(requestDataMessage.getData(), replyData, replyError);

    //add handler to queue and wait for handling
    messageQueue.pushSafe(handler.get());
    handler->waitForCompletion(); //wait_for żeby ustawić timeout wykonania

    DataMessage replyDataMessage(requestDataMessage.getType(), replyData, replyError);

    this->socket.send(clientAddress, replyDataMessage.serialize());
    ConfirmMessage confirm(this->socket.receive(clientAddress));
    std::cout << "Request " << std::to_string(requestDataMessage.getType()) << " from " << clientAddress.toString() << " completed." << std::endl;
    counter.leave();
    delete this;
}

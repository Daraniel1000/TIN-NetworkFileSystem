#include <session/messages/ConfirmMessage.h>
#include <session/messages/DataMessage.h>
#include <mutex>
#include <iostream>
#include <transport/socket_error.h>
#include <addresses/address_error.h>
#include <transport/timeout_error.h>
#include <sstream>
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
    int error = 0;
    try {
        this->socket.send(clientAddress, ConfirmMessage().serialize());

        DataMessage requestDataMessage(this->socket.receive(clientAddress, 5));

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
        int timeoutCount = 0;
        int confirmation = 0;
        while(timeoutCount < 5 && confirmation == 0) {
            try {
                ConfirmMessage confirm(this->socket.receive(clientAddress));
                confirmation = 1;
            }
            catch (timeout_error &e) {
                error = 6000;
                std::cout << "Timeout error. " + std::string(e.what()) << std::endl;
                this->socket.send(clientAddress, replyDataMessage.serialize());
                timeoutCount++;
            }
        }
        std::cout << "Request " << std::to_string(requestDataMessage.getType()) << " from " << clientAddress.toString()
                  << " completed." << std::endl;
        counter.leave();
        delete this;
    }
    catch(std::out_of_range& e){
        error = 7000;
        std::cout<< "Unknown request type" << std::endl;
        this->socket.send(clientAddress, DataMessage(0, DomainData(), PlainError(-1)).serialize());
    }
    catch (timeout_error& e)
    {
        error = 6000;
        std::cout <<"Timeout error. " + std::string(e.what()) << std::endl;
    }
    catch (address_error& e)
    {
        error = 1000 + 100*e.getMajorCode() + e.getMinorCode();
        std::cout << "Bad host address. " + std::string(e.what()) << std::endl;
    }
    catch (socket_error& e)
    {
        error = 3000 + 100*e.getMajorCode() + e.getMinorCode();
        std::cout <<"Network error. " + std::string(e.what()) << std::endl;
    }
    catch (std::exception& e)
    {
        error = 5000;
        std::cout <<"Unknown error. " + std::string(e.what()) << std::endl;
    }
    if(error != 0)
    {
        std::stringstream temp;
        temp << error;
        const char* errorArray = temp.str().c_str();
        std::cout << errorArray;
    }

}

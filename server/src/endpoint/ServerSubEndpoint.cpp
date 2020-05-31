#include <session/messages/ConfirmMessage.h>
#include <session/messages/DataMessage.h>
#include <mutex>
#include <iostream>
#include <transport/socket_error.h>
#include <addresses/address_error.h>
#include <transport/timeout_error.h>
#include <sstream>
#include <application/mynfs/bad_argument_error.h>
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
        PlainData data;
        while(timeoutCount < 5 && confirmation == 0) {
            try {
                data = this->socket.receive(clientAddress, 5);
                ConfirmMessage confirm(data);
                confirmation = 1;
            }
            catch (timeout_error &e) {
                error = 6000;
                std::cout << std::to_string(error) + " Timeout error. " + std::string(e.what()) << std::endl;
                this->socket.send(clientAddress, replyDataMessage.serialize());
                timeoutCount++;
            }
            catch (socket_error& e)
            {
                error = 3000 + 100*e.getMajorCode() + e.getMinorCode();
                std::cout <<std::to_string(error) +" Network error. " + std::string(e.what()) << std::endl;
                timeoutCount++;
            }
            catch(std::logic_error &e){ //Unable to create ConfirmMessage, possibly it is DataMessage
                try{

                    DataMessage repeatedData(data);
                    this->socket.send(clientAddress, replyDataMessage.serialize());
                    timeoutCount++;
                    std::cout << "Reply resend." << std::endl;
                }
                catch (socket_error& e)
                {
                    error = 3000 + 100*e.getMajorCode() + e.getMinorCode();
                    std::cout <<std::to_string(error) +" Network error. " + std::string(e.what()) << std::endl;
                    timeoutCount++;
                }
            }
        }
        if(confirmation == 1)
            std::cout << "Request " << std::to_string(requestDataMessage.getType()) << " from " << clientAddress.toString()
                  << " completed." << std::endl;
        else
            std::cout << "Request " << std::to_string(requestDataMessage.getType()) << " from " << clientAddress.toString()
                      << " failed to receive confirmation." << std::endl;
    }
    catch(std::out_of_range& e){
        error = 7000;
        std::cout<< "Unknown request type" << std::endl;
        this->socket.send(clientAddress, DataMessage(0, DomainData(), PlainError(-1)).serialize());
    }
    catch (timeout_error& e)
    {
        error = 6000;
        std::cout <<std::to_string(error) +" Timeout error. " + std::string(e.what()) << std::endl;
    }
    catch (address_error& e)
    {
        error = 1000 + 100*e.getMajorCode() + e.getMinorCode();
        std::cout << std::to_string(error) +" Bad host address. " + std::string(e.what()) << std::endl;
    }
    catch (bad_argument_error& e)
    {
        error = 2000 + 100*e.getMajorCode() + e.getMinorCode();
        std::cout << std::to_string(error) + " Bad request argument. " + std::string(e.what());
    }
    catch (socket_error& e)
    {
        error = 3000 + 100*e.getMajorCode() + e.getMinorCode();
        std::cout <<std::to_string(error) +" Network error. " + std::string(e.what()) << std::endl;
    }
    catch (std::exception& e)
    {
        error = 5000;
        std::cout <<std::to_string(error) +" Unknown error. " + std::string(e.what()) << std::endl;
    }

    counter.leave();
    delete this;

}

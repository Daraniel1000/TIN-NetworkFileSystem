#include <session/messages/RequestMessage.h>
#include <addresses/EphemeralPort.h>
#include <thread>
#include <transport/read_interrupted_error.h>
#include <session/messages/ConfirmMessage.h>
#include "ServerEndpoint.h"
#include "ServerSubEndpoint.h"
#include "../execution/Executor/Executor.h"
#include "../TerminalListener.h"


ServerEndpoint::ServerEndpoint(Port port, const std::string &baseDir, const std::string &fsDir,
                               const std::string &hostsFile) : socket(port),
                                                               accessManager(baseDir,
                                                                             fsDir, hostsFile)
{}

void ServerEndpoint::run()
{
    Executor executor(messageQueue);
    TerminalListener listener(socket);
    executor.serverStop.lock();
    listener.serverStop.lock();
    std::thread listenerThread(&TerminalListener::run, &listener);
    std::thread executorThread(&Executor::run, &executor);

    NetworkAddress source{};
    ServerSubEndpoint *subEndpoint;

    while (!listener.serverStop.try_lock())
    {
        try
        {
            RequestMessage request(socket.receive(source));

            std::cout << "New request from " << source.toString() << std::endl;

            if (accessManager.isPermitted(source.getAddress()))
            {

                //run new thread here and go back to receiving on socket
                subEndpoint = new ServerSubEndpoint(source, this->handlerFactoryPool,
                                                    this->messageQueue, this->counter, this->accessManager);
                counter.enter();
                std::thread thread(&ServerSubEndpoint::run, subEndpoint);
                thread.detach();
            }
            else
            {
                this->socket.send(source, ConfirmMessage(PlainError(-1)).serialize());
            }
        }
        catch(std::logic_error& e){
            std::cout << "8000 First received message is not a RequestMessage" << std::endl;
        }
        catch (read_interrupted_error&){}
        catch (std::runtime_error &e) {
            std::cout << "5000 " + std::string(e.what()) << std::endl;
        }
    }
    listener.serverStop.unlock();
    listenerThread.join();
    counter.await();
    executor.serverStop.unlock();
    messageQueue.notify();
    executorThread.join();
    listener.writeQuit();
}

const NetworkAddress &ServerEndpoint::getAddress() const
{
    return this->socket.getAddress();
}

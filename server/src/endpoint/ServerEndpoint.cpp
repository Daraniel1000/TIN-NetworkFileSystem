#include <session/messages/RequestMessage.h>
#include <addresses/EphemeralPort.h>
#include <thread>
#include "ServerEndpoint.h"
#include "ServerSubEndpoint.h"
#include "../execution/Executor/Executor.h"
#include "../TerminalListener.h"


ServerEndpoint::ServerEndpoint(Port port) : socket(port) {}

void ServerEndpoint::run()
{
    Executor executor(messageQueue);
    TerminalListener listener;
    executor.serverStop.lock();
    std::thread listenerThread(&TerminalListener::run, &listener);
    std::thread executorThread(&Executor::run, &executor);

    NetworkAddress source{};

    while(!listener.serverStop.try_lock()) {
        RequestMessage request(socket.receive(source));

        //run new thread here and go back to receiving on socket
        ServerSubEndpoint subEndpoint(UDPSocket(EphemeralPort()), source, this->handlerFactoryPool, this->messageQueue, this->counter);
        counter.enter();
        std::thread thread(&ServerSubEndpoint::run, &subEndpoint);

        thread.detach();
    }
    listener.serverStop.unlock();
    listenerThread.join();
    counter.await();
    executor.serverStop.unlock();
    messageQueue.notify();
    executorThread.join();
}

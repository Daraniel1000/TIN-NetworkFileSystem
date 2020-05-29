#ifndef MYNFS_SERVERENDPOINT_H
#define MYNFS_SERVERENDPOINT_H


#include <transport/socket/UDPSocket.h>
#include <addresses/Port.h>
#include <queue>
#include "../execution/HandlerFactoryPool.h"
#include "../SafeQueue.h"
#include "../ThreadCounter.h"

class ServerEndpoint
{
    UDPSocket socket;
    HandlerFactoryPool handlerFactoryPool;
    SafeQueue<Handler*> messageQueue;      //queue of pointers, subendpoint keeps ownership of handler for mutex
    ThreadCounter counter;
public:
    /**
     * Create server at given port
     */
    ServerEndpoint(Port port);

    /**
     * Run server
     */
    void run();

    const NetworkAddress& getAddress() const;

    /**
     * TODO: stop the server somehow
     */
};


#endif //MYNFS_SERVERENDPOINT_H

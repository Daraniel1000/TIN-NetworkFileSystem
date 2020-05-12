#ifndef MYNFS_SERVERENDPOINT_H
#define MYNFS_SERVERENDPOINT_H


#include <transport/socket/Socket.h>
#include <addresses/Port.h>
#include <queue>
#include "../execution/HandlerFactoryPool.h"

class ServerEndpoint
{
    Socket socket;
    HandlerFactoryPool handlerFactoryPool;
    std::queue<Handler*> messageQueue;      //queue of pointers, subendpoint keeps ownership of handler for mutex
public:
    /**
     * Create server at given port
     */
    ServerEndpoint(Port port);

    /**
     * Run server
     * TODO: preferably run on another thread
     */
    void run();

    /**
     * TODO: stop the server somehow
     */
};


#endif //MYNFS_SERVERENDPOINT_H

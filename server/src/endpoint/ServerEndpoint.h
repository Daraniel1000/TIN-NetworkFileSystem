#ifndef MYNFS_SERVERENDPOINT_H
#define MYNFS_SERVERENDPOINT_H


#include <transport/socket/Socket.h>
#include <addresses/Port.h>
#include "../execution/HandlerFactoryPool.h"

class ServerEndpoint
{
    Socket socket;
    HandlerFactoryPool handlerFactoryPool;
public:
    ServerEndpoint(Port port);

    void run();
};


#endif //MYNFS_SERVERENDPOINT_H

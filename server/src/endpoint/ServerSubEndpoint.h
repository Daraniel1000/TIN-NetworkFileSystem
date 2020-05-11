#ifndef MYNFS_SERVERSUBENDPOINT_H
#define MYNFS_SERVERSUBENDPOINT_H


#include <transport/socket/Socket.h>
#include "../execution/HandlerFactoryPool.h"

class ServerSubEndpoint
{
    Socket socket;
    NetworkAddress clientAddress;
    const HandlerFactoryPool& handlerFactoryPool;
public:
    ServerSubEndpoint(Socket socket, NetworkAddress clientAddress, const HandlerFactoryPool& handlerFactoryPool);

    void run();
};


#endif //MYNFS_SERVERSUBENDPOINT_H

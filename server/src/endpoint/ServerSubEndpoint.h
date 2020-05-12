#ifndef MYNFS_SERVERSUBENDPOINT_H
#define MYNFS_SERVERSUBENDPOINT_H


#include <transport/socket/Socket.h>
#include <queue>
#include "../execution/HandlerFactoryPool.h"

class ServerSubEndpoint
{
    Socket socket;
    NetworkAddress clientAddress;
    const HandlerFactoryPool& handlerFactoryPool;
    std::queue<Handler*>& messageQueue;     //TODO zaimplementować safe queue
public:
    /**
     * Create server subendpoint (for further communication with the client)
     * @param socket socket to use
     * @param clientAddress address of the client (from first request)
     * @param handlerFactoryPool handler factory passed from main server
     */
    ServerSubEndpoint(Socket socket, NetworkAddress clientAddress, const HandlerFactoryPool& handlerFactoryPool,
            std::queue<Handler*>& queueRef);

    /**
     * Run subendpoint
     * TODO: preferably run on yet another thread (not main server thread)
     */
    void run();

    /**
     * TODO: stop the subendpoint somehow
     */
};


#endif //MYNFS_SERVERSUBENDPOINT_H

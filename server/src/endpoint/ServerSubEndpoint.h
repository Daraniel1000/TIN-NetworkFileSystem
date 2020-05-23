#ifndef MYNFS_SERVERSUBENDPOINT_H
#define MYNFS_SERVERSUBENDPOINT_H


#include <transport/socket/UDPSocket.h>
#include <queue>
#include "../execution/HandlerFactoryPool.h"
#include "../SafeQueue.h"
#include "../ThreadCounter.h"

class ServerSubEndpoint
{
    UDPSocket socket;
    NetworkAddress clientAddress;
    const HandlerFactoryPool& handlerFactoryPool;
    SafeQueue<Handler*>& messageQueue;
    ThreadCounter& counter;
public:
    /**
     * Create server subendpoint (for further communication with the client)
     * @param socket socket to use
     * @param clientAddress address of the client (from first request)
     * @param handlerFactoryPool handler factory passed from main server
     */
    ServerSubEndpoint(UDPSocket socket, NetworkAddress clientAddress, const HandlerFactoryPool& handlerFactoryPool,
            SafeQueue<Handler*>& queueRef, ThreadCounter& counterRef);

    /**
     * Run subendpoint
     */
    void run();

    /**
     * TODO: stop the subendpoint somehow
     */
};


#endif //MYNFS_SERVERSUBENDPOINT_H

#ifndef MYNFS_SERVERSUBENDPOINT_H
#define MYNFS_SERVERSUBENDPOINT_H


#include <transport/socket/UDPSocket.h>
#include <queue>
#include <addresses/EphemeralPort.h>
#include "../execution/HandlerFactoryPool.h"
#include "../SafeQueue.h"
#include "../ThreadCounter.h"
#include "../AccessManager.h"

class ServerSubEndpoint
{
    UDPSocket socket;
    NetworkAddress clientAddress;
    const HandlerFactoryPool &handlerFactoryPool;
    SafeQueue<Handler *> &messageQueue;
    ThreadCounter &counter;
    AccessManager &accessManager;
public:
    /**
     * Create server subendpoint (for further communication with the client)
     * @param clientAddress address of the client (from first request)
     * @param handlerFactoryPool handler factory passed from main server
     * @param port port to use
     */
    ServerSubEndpoint(NetworkAddress clientAddress, const HandlerFactoryPool &handlerFactoryPool,
                      SafeQueue<Handler *> &queueRef, ThreadCounter &counterRef, AccessManager &accessManager,
                      Port port = EphemeralPort());

    /**
     * Run subendpoint
     */
    void run();

    /**
     * TODO: stop the subendpoint somehow
     */
};


#endif //MYNFS_SERVERSUBENDPOINT_H

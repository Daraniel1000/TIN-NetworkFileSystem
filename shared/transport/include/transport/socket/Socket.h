#ifndef MYNFS_SOCKET_H
#define MYNFS_SOCKET_H

#include <addresses/Port.h>
#include <addresses/NetworkAddress.h>
#include "transport/PlainData.h"

class Socket
{
public:
    /**
     * Creates new socket at given port
     * @param port Port to create socket at, passing EphemeralPort will create socket at any free ephemeral port
     */
    Socket(Port port);

    /**
     * Closes the socket
     */
    ~Socket();

    /**
     * Send data to recipient
     * @param recipient network address of recipient
     * @param message serialized message
     */
    void send(NetworkAddress recipient, const PlainData& message);

    /**
     * Get data from anyone
     * Blocks until data received
     * @param source reference to address structure, that will be filled with address info of the source of the message
     * @return serialized received message
     */
    PlainData receive(NetworkAddress& source);

    /**
     * Wake up blocked socket
     * Has to be called from another thread obviously
     */
    void signal();
};


#endif //MYNFS_SOCKET_H

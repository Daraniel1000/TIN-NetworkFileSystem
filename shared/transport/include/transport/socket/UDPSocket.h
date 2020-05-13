#ifndef MYNFS_UDPSOCKET_H
#define MYNFS_UDPSOCKET_H

#include <sys/socket.h>
#include <addresses/Port.h>
#include <addresses/NetworkAddress.h>
#include "transport/PlainData.h"

class UDPSocket
{
    const static int FAMILY = AF_INET;
    const static int TYPE = SOCK_DGRAM;

    int socketDescriptor;
    NetworkAddress socketAddress;

    int signalPipeRead;
    int signalPipeWrite;

    const static int READ_BUFFER_SIZE = 65507;
    std::byte readBuffer[READ_BUFFER_SIZE];

public:
    /**
     * Creates new socket at given port
     * @param port Port to create socket at, passing EphemeralPort will create socket at any free ephemeral port
     */
    UDPSocket(Port port);

    /**
     * Closes the socket
     */
    ~UDPSocket();

    /**
     * Send data to recipient
     * @param recipient network address of recipient
     * @param message serialized message
     */
    void send(NetworkAddress recipient, const PlainData& message) const;

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
    void signal() const;
};


#endif //MYNFS_UDPSOCKET_H

#ifndef MYNFS_NETWORKADDRESS_H
#define MYNFS_NETWORKADDRESS_H


#include <netinet/in.h>
#include <string>
#include "IpAddress.h"
#include "Port.h"

class NetworkAddress
{
    IpAddress ipAddress;
    Port port;

public:
    NetworkAddress() = default;
    NetworkAddress(IpAddress ipAddress, Port port);

    /**
    * Construct NetworkAddress from string
    * If port is not specified it will be set to 0
    * @param addressString null-terminated address (IpAddress:Port)
    */
    NetworkAddress(char const* address);

    const IpAddress& getAddress() const;
    const Port& getPort() const;

    void setAddress(IpAddress newAddress);
    void setPort(Port newPort);

    /**
     * Get sockaddr_in struct with network order
     */
    sockaddr_in toStruct() const;

    /**
     * Get address string in address:port format (eg. 127.0.0.1:22)
     */
    std::string toString() const;
};


#endif //MYNFS_NETWORKADDRESS_H

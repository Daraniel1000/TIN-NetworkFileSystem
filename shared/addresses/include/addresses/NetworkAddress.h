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

    const IpAddress& getAddress() const;
    const Port& getPort() const;

    void setAddress(IpAddress newAddress);
    void setPort(Port newPort);

    sockaddr_in toStruct() const;
    std::string toString() const;
};


#endif //MYNFS_NETWORKADDRESS_H

#ifndef MYNFS_NETWORKADDRESS_H
#define MYNFS_NETWORKADDRESS_H


#include "IpAddress.h"
#include "Port.h"

class NetworkAddress
{
    IpAddress ipAddress;
    Port port;

public:
    NetworkAddress() = default;
    NetworkAddress(IpAddress ipAddress, Port port) : ipAddress(ipAddress), port(port)  {}

    const IpAddress& getAddress() { return this->ipAddress; }
    const Port& getPort() { return this->port; }

    void setAddress(IpAddress newAddress) { this->ipAddress = newAddress; }
    void setPort(Port newPort) { this->port = newPort; }
};


#endif //MYNFS_NETWORKADDRESS_H

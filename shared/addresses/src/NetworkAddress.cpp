#include <arpa/inet.h>
#include <cstring>
#include <sstream>
#include "addresses/NetworkAddress.h"

NetworkAddress::NetworkAddress(IpAddress ipAddress, Port port) : ipAddress(ipAddress), port(port)
{}

const IpAddress &NetworkAddress::getAddress() const
{
    return this->ipAddress;
}

const Port &NetworkAddress::getPort() const
{
    return this->port;
}

void NetworkAddress::setAddress(IpAddress newAddress)
{
    this->ipAddress = newAddress;
}

void NetworkAddress::setPort(Port newPort)
{
    this->port = newPort;
}

sockaddr_in NetworkAddress::toStruct() const
{
    return sockaddr_in{AF_INET,
                       this->port.toNetworkOrder(),
                       this->getAddress().toNetworkOrder()};
}

std::string NetworkAddress::toString() const
{
    char buf[INET_ADDRSTRLEN];
    struct in_addr inaddr;
    inaddr.s_addr = this->getAddress().toNetworkOrder();
    inet_ntop(AF_INET, &inaddr, buf, sizeof(buf));
    std::stringstream temp;
    temp << this->port.toHostOrder();
    const char* portArray = temp.str().c_str();
    strcat(buf, ":");
    strcat(buf, portArray);
    return buf;
}

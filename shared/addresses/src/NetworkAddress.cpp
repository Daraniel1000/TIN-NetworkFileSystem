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
                       this->getAddress().toNetworkOrder(),
                       0}; //TODO, zrobiłem to nasz szybko, może się da lepiej
}

std::string NetworkAddress::toString() const
{
    return std::string(); //TODO
}

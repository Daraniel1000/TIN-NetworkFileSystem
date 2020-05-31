#include <arpa/inet.h>
#include <cstring>
#include <sstream>
#include "addresses/NetworkAddress.h"
#include "addresses/EphemeralPort.h"

NetworkAddress::NetworkAddress(IpAddress ipAddress, Port port) : ipAddress(ipAddress), port(port)
{}

NetworkAddress::NetworkAddress(char const* address)
{
    char *ip, *portNo, *addressCopy = strdup(address);
    ip = strtok(addressCopy, ":");
    if(ip == NULL) {
        this->ipAddress = IpAddress(addressCopy);
        this->port = EphemeralPort();
    }
    else {
        this->ipAddress = IpAddress(ip);
        portNo = strtok(NULL, ":");
        if (portNo == NULL)
            this->port = EphemeralPort();
        else
            this->port = Port(atoi(portNo));
    }
    free(addressCopy);
}

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

bool NetworkAddress::operator==(const NetworkAddress &rhs) const
{
    return ipAddress == rhs.ipAddress &&
           port == rhs.port;
}

bool NetworkAddress::operator!=(const NetworkAddress &rhs) const
{
    return !(rhs == *this);
}

bool NetworkAddress::operator<(const NetworkAddress &rhs) const
{
    if (ipAddress < rhs.ipAddress)
        return true;
    if (rhs.ipAddress < ipAddress)
        return false;
    return port < rhs.port;
}

bool NetworkAddress::operator>(const NetworkAddress &rhs) const
{
    return rhs < *this;
}

bool NetworkAddress::operator<=(const NetworkAddress &rhs) const
{
    return !(rhs < *this);
}

bool NetworkAddress::operator>=(const NetworkAddress &rhs) const
{
    return !(*this < rhs);
}

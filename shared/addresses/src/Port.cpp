#include <netinet/in.h>
#include "addresses/Port.h"

Port::Port(uint16_t port) : port(port) {}

uint16_t Port::toNetworkOrder() const
{
    return htons(this->port);
}

uint16_t Port::toHostOrder() const
{
    return this->port;
}

bool Port::operator==(const Port &rhs) const
{
    return port == rhs.port;
}

bool Port::operator!=(const Port &rhs) const
{
    return !(rhs == *this);
}

bool Port::operator<(const Port &rhs) const
{
    return port < rhs.port;
}

bool Port::operator>(const Port &rhs) const
{
    return rhs < *this;
}

bool Port::operator<=(const Port &rhs) const
{
    return !(rhs < *this);
}

bool Port::operator>=(const Port &rhs) const
{
    return !(*this < rhs);
}




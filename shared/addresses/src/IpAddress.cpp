#include "addresses/IpAddress.h"

IpAddress::IpAddress(uint32_t address) : address(address) {}

IpAddress::IpAddress(char *addressString)
{

}

uint32_t IpAddress::toNetworkOrder() const
{
    return 0;
}

uint32_t IpAddress::toHostOrder() const
{
    return 0;
}
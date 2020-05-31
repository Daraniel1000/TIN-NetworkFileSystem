#ifndef MYNFS_IPADDRESS_H
#define MYNFS_IPADDRESS_H


#include <cstdint>
#include <cstdlib>

class IpAddress
{
    uint32_t address;
public:
    /**
     * Empty default constructor for creating default empty objects
     */
    IpAddress() = default;

    IpAddress(uint32_t address);

    /**
     * Construct IpAddress from string
     * If it's a numerical address just convert string to numerical representation
     * If it's a name, query the resolver
     * @param addressString null-terminated address (numerical or name)
     */
    IpAddress(char const *addressString);

    uint32_t toNetworkOrder() const;

    uint32_t toHostOrder() const;

    bool operator==(const IpAddress &rhs) const;

    bool operator!=(const IpAddress &rhs) const;

    bool operator<(const IpAddress &rhs) const;

    bool operator>(const IpAddress &rhs) const;

    bool operator<=(const IpAddress &rhs) const;

    bool operator>=(const IpAddress &rhs) const;

};


#endif //MYNFS_IPADDRESS_H

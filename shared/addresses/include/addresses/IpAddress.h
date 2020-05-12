#ifndef MYNFS_IPADDRESS_H
#define MYNFS_IPADDRESS_H


class IpAddress
{
    int address = 0;
public:
    /**
     * Empty default constructor for creating default empty objects
     */
    IpAddress() = default;

    /**
     * Construct IpAddress from string
     * If it's a numerical address just convert string to numerical representation
     * If it's a name, query the resolver
     * @param addressString null-terminated address (numerical or name)
     */
    IpAddress(char *addressString);

    /**
     * TODO:
     * getters but i don't know the exact form of them yet
     */
};


#endif //MYNFS_IPADDRESS_H

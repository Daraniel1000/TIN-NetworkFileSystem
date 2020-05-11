#ifndef MYNFS_IPADDRESS_H
#define MYNFS_IPADDRESS_H


class IpAddress
{
    int address = 0;
public:
    IpAddress() = default;
    IpAddress(char *addressString);
};


#endif //MYNFS_IPADDRESS_H

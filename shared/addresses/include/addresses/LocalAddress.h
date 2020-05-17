#ifndef MYNFS_LOCALADDRESS_H
#define MYNFS_LOCALADDRESS_H

#include "IpAddress.h"

class LocalAddress : public IpAddress
{
/**
 * just a "shortcut" for writing IpAddress("127.0.0.1")
 */
public:
    LocalAddress():IpAddress("127.0.0.1"){}
};

#endif //MYNFS_LOCALADDRESS_H

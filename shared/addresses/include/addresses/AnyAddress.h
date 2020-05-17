#ifndef MYNFS_ANYADDRESS_H
#define MYNFS_ANYADDRESS_H

#include "IpAddress.h"

class AnyAddress : public IpAddress
{
/**
 * just a "shortcut" for writing IpAddress(INADDR_ANY)
 */
public:
 AnyAddress():IpAddress(INADDR_ANY){}
};

#endif //MYNFS_ANYADDRESS_H

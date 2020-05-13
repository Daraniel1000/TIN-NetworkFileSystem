#ifndef MYNFS_ANYADDRESS_H
#define MYNFS_ANYADDRESS_H

#include "IpAddress.h"

class AnyAddress : public IpAddress
{
/**
 * TODO:
 * just a "shortcut" for writing IpAddress(INADDR_ANY)
 * just create a constructor without arguments and create IpAddress(INADDR_ANY)
 */
};

#endif //MYNFS_ANYADDRESS_H

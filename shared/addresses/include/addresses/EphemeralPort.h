#ifndef MYNFS_EPHEMERALPORT_H
#define MYNFS_EPHEMERALPORT_H

#include "Port.h"

class EphemeralPort : public Port
{
/**
 * just a "shortcut" for writing Port(0)
 */
public:
 EphemeralPort():Port(0){}
};

#endif //MYNFS_EPHEMERALPORT_H

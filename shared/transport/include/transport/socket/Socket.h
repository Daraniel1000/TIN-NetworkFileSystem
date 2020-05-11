#ifndef MYNFS_SOCKET_H
#define MYNFS_SOCKET_H

#include <addresses/Port.h>
#include <addresses/IpAddress.h>
#include "transport/PlainData.h"

class Socket
{
public:
    Socket(Port port);

    void send(IpAddress address, Port port, const PlainData& message);
    PlainData receive();

    void signal();
    void close();
};


#endif //MYNFS_SOCKET_H

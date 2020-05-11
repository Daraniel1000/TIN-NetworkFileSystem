#ifndef MYNFS_SOCKET_H
#define MYNFS_SOCKET_H

#include <addresses/Port.h>
#include <addresses/NetworkAddress.h>
#include "transport/PlainData.h"

class Socket
{
public:
    Socket(Port port);

    void send(NetworkAddress recipient, const PlainData& message);
    PlainData receive(NetworkAddress& source);

    void signal();
    void close();
};


#endif //MYNFS_SOCKET_H

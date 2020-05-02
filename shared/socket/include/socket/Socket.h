#ifndef MYNFS_SOCKET_H
#define MYNFS_SOCKET_H

#include <addresses/Port.h>
#include <addresses/IpAddress.h>
#include <messages/Message.h>

class Socket
{
public:
    Socket(Port port);

    void send(IpAddress address, Port port, const Message& message);
    PlainData receive(IpAddress address);

    void close();
};


#endif //MYNFS_SOCKET_H

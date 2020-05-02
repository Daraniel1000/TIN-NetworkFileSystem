#ifndef MYNFS_CLIENTENDPOINT_H
#define MYNFS_CLIENTENDPOINT_H

#include <socket/Socket.h>
#include <addresses/IpAddress.h>
#include <addresses/Port.h>
#include <addresses/EphemeralPort.h>
#include <protocol/requests/Request.h>

class ClientEndpoint
{
    Socket socket;

public:
    ClientEndpoint(Port port = EphemeralPort());
    ~ClientEndpoint();

    DataMessage send(IpAddress serverAddress, Port port, const Request& request);
};


#endif //MYNFS_CLIENTENDPOINT_H

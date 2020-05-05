#ifndef MYNFS_CLIENTENDPOINT_H
#define MYNFS_CLIENTENDPOINT_H

#include <transport/socket/Socket.h>
#include <addresses/IpAddress.h>
#include <addresses/Port.h>
#include <addresses/EphemeralPort.h>
#include <application/mynfs/requests/Request.h>

class ClientEndpoint
{
    Socket socket;

public:
    ClientEndpoint(Port port = EphemeralPort());
    ~ClientEndpoint();

    template<class Req, class Rep>
    Rep send(IpAddress serverAddress, Port port, const Req& request);
};


#endif //MYNFS_CLIENTENDPOINT_H

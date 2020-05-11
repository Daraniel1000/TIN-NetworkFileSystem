#ifndef MYNFS_CLIENTENDPOINT_H
#define MYNFS_CLIENTENDPOINT_H

#include <transport/socket/Socket.h>
#include <addresses/Port.h>
#include <addresses/EphemeralPort.h>
#include <application/mynfs/requests/Request.h>
#include <addresses/NetworkAddress.h>

class ClientEndpoint
{
    Socket socket;

public:
    ClientEndpoint(Port port = EphemeralPort());
    ~ClientEndpoint();

    template<class Req, class Rep>
    Rep send(NetworkAddress recipient, const Req& request);
};


#endif //MYNFS_CLIENTENDPOINT_H

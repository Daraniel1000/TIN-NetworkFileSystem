#ifndef MYNFS_CLIENTENDPOINT_H
#define MYNFS_CLIENTENDPOINT_H

#include <transport/socket/UDPSocket.h>
#include <addresses/Port.h>
#include <addresses/EphemeralPort.h>
#include <application/mynfs/requests/Request.h>
#include <addresses/NetworkAddress.h>

class ClientEndpoint
{
    UDPSocket socket;

public:
    /**
     * Create Endpoint
     * @param port port to operate on (defualts to ephemeral port)
     */
    ClientEndpoint(Port port = EphemeralPort());
    ~ClientEndpoint();

    /**
     * Send request to recipient and get reply
     * Templated because client knows what type od request he is sending
     * @tparam Req specialized request class
     * @tparam Rep specialized reply class
     * @param recipient recipient address
     * @param request request object
     * @return reply
     */
    template<class Req, class Rep>
    Rep send(NetworkAddress recipient, const Req& request);
};


#endif //MYNFS_CLIENTENDPOINT_H

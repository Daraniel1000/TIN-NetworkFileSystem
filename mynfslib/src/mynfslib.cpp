#include <application/mynfs/requests/OpenRequest.h>
#include <application/mynfs/replies/OpenReply.h>
#include "mynfslib.h"
#include "endpoint/ClientEndpoint.h"

int16_t mynfs_open(char *host, char *path, uint8_t oflag)
{
    ClientEndpoint clientEndpoint;

    OpenReply readReply = clientEndpoint.send<OpenRequest, OpenReply>
                                        (
                                            IpAddress(host),
                                            Port(),
                                            OpenRequest(path, oflag)
                                        );

    return readReply.getDescriptor();
}
#include <application/mynfs/requests/OpenRequest.h>
#include <application/mynfs/requests/ReadRequest.h>
#include <application/mynfs/replies/OpenReply.h>
#include <application/mynfs/replies/ReadReply.h>
#include "mynfslib.h"
#include "endpoint/ClientEndpoint.h"

int16_t mynfs_open(char *host, char *path, uint8_t oflag)
{
    ClientEndpoint clientEndpoint;

    OpenReply readReply = clientEndpoint.send<OpenRequest, OpenReply>
                                        (
                                            NetworkAddress(IpAddress(host), Port()),
                                            OpenRequest(path, oflag)
                                        );

    return readReply.getDescriptor();
}

int16_t mynfs_read(char *host, int16_t fd, void *buf, int16_t count)
{
    ClientEndpoint clientEndpoint;

    ReadReply readReply = clientEndpoint.send<ReadRequest, ReadReply>
            (
                    NetworkAddress(IpAddress(host), Port()),
                    ReadRequest(fd, buf, count)
            );

    return readReply.getDataSize();
}
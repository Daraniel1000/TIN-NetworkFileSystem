#include <application/mynfs/replies/OpenReply.h>
#include <application/mynfs/requests/OpenRequest.h>
#include <application/mynfs/replies/ReadReply.h>
#include <application/mynfs/requests/ReadRequest.h>
#include <application/mynfs/replies/WriteReply.h>
#include <application/mynfs/requests/WriteRequest.h>
#include <application/mynfs/replies/LseekReply.h>
#include <application/mynfs/requests/LseekRequest.h>
#include <application/mynfs/replies/CloseReply.h>
#include <application/mynfs/requests/CloseRequest.h>
#include <application/mynfs/replies/UnlinkReply.h>
#include <application/mynfs/requests/UnlinkRequest.h>
#include "mynfslib.h"
#include "endpoint/ClientEndpoint.h"

int16_t mynfs_open(char *host, char *path, uint8_t oflag)
{
    // create endpoint
    ClientEndpoint clientEndpoint;

    // send request and get reply
    OpenReply readReply = clientEndpoint.send<OpenRequest, OpenReply>
                                        (
                                            NetworkAddress(IpAddress(host), Port()),
                                            OpenRequest(path, oflag)
                                        );
    // react to error here
    readReply.getError();

    // return reply data
    return readReply.getDescriptor();
}

int16_t mynfs_read(char *host, int16_t fd, void *buf, int16_t count)
{
    ClientEndpoint clientEndpoint;

    ReadReply readReply = clientEndpoint.send<ReadRequest, ReadReply>
            (
                    NetworkAddress(IpAddress(host), Port()),
                    ReadRequest(fd, count)
            );

    return readReply.getData().getSize();
}
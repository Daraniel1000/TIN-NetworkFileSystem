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
#include <mynfslib.h>

#include "mynfslib.h"
#include "endpoint/ClientEndpoint.h"

int16_t mynfs_open(char const *host, char const *path, uint8_t oflag)
{
    // create endpoint
    ClientEndpoint clientEndpoint;

    // send request and get reply
    OpenReply readReply = clientEndpoint.send<OpenRequest, OpenReply>
                                        (
                                            NetworkAddress(host),
                                            OpenRequest(path, oflag)
                                        );
    // react to error here
    readReply.getError();

    // return reply data
    return readReply.getDescriptor();
}

int16_t mynfs_read(char const *host, int16_t fd, void *buf, int16_t count)
{
    // create endpoint
    ClientEndpoint clientEndpoint;

    // send request and get reply
    ReadReply readReply = clientEndpoint.send<ReadRequest, ReadReply>
            (
                    NetworkAddress(host),
                    ReadRequest(fd, count)
            );

    // react to error here
    readReply.getError();

    //return
    return readReply.getData().getSize();
}

int16_t mynfs_write(char *host, int16_t fd, void *buf, int16_t count)
{
    // create endpoint
    ClientEndpoint clientEndpoint;

    // send request and get reply
    WriteReply readReply = clientEndpoint.send<WriteRequest, WriteReply>
            (
                    NetworkAddress(host),
                    WriteRequest(fd, buf,count)
            );

    // react to error here
    readReply.getError();

    return readReply.getCount();
}

int32_t mynfs_lseek(char *host, int16_t fd, int32_t offset, uint8_t whence)
{
    // create endpoint
    ClientEndpoint clientEndpoint;

    // send request and get reply
    LseekReply readReply = clientEndpoint.send<LseekRequest, LseekReply>
            (
                    NetworkAddress(host),
                    LseekRequest(fd, offset, whence)
            );

    // react to error here
    readReply.getError();

    //return offset
    return readReply.getOffset();
}

int8_t mynfs_close(char *host, int16_t fd)
{
    // create endpoint
    ClientEndpoint clientEndpoint;

    // send request and get reply
    CloseReply readReply = clientEndpoint.send<CloseRequest, CloseReply>
            (
                    NetworkAddress(host),
                    CloseRequest(fd)
            );

    // react to error here
    readReply.getError();

   return 0;
}

int8_t mynfs_unlink(char *host, char *path)
{
    // create endpoint
    ClientEndpoint clientEndpoint;

    // send request and get reply
    UnlinkReply readReply = clientEndpoint.send<UnlinkRequest, UnlinkReply>
            (
                    NetworkAddress(host),
                    UnlinkRequest(path)
            );

    // react to error here
    readReply.getError();

    return 0;
}

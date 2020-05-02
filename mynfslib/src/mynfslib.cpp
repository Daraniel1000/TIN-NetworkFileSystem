#include <protocol/requests/OpenRequest.h>
#include <messages/DataMessage.h>
#include <protocol/replies/OpenReply.h>
#include "mynfslib.h"
#include "endpoint/ClientEndpoint.h"

int16_t mynfs_open(char *host, char *path, uint8_t oflag)
{
    ClientEndpoint clientEndpoint;

    DataMessage reply = clientEndpoint.send(IpAddress(host), Port(), OpenRequest(path, oflag));

    OpenReply readReply(reply);

    return readReply.getDescriptor();
}
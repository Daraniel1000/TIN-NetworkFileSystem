#include <messages/ConfirmMessage.h>
#include <messages/DataMessage.h>
#include <messages/RequestMessage.h>
#include "ClientEndpoint.h"

ClientEndpoint::ClientEndpoint(Port port) : socket(port) {}

ClientEndpoint::~ClientEndpoint()
{
    this->socket.close();
}

DataMessage ClientEndpoint::send(IpAddress serverAddress, Port port, const Request& request)
{
    socket.send(serverAddress, port, RequestMessage(request.getType()));
    ConfirmMessage requestConfirm(socket.receive(serverAddress));
    socket.send(serverAddress, port, DataMessage(request.getData()));
    DataMessage replyData(socket.receive(serverAddress));
    socket.send(serverAddress, port, ConfirmMessage());

    return replyData;
}

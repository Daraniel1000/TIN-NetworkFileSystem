#include <session/messages/ConfirmMessage.h>
#include <session/messages/DataMessage.h>
#include <session/messages/RequestMessage.h>
#include <application/mynfs/replies/OpenReply.h>
#include <application/mynfs/requests/OpenRequest.h>
#include "ClientEndpoint.h"

ClientEndpoint::ClientEndpoint(Port port) : socket(port) {}

ClientEndpoint::~ClientEndpoint()
{
    this->socket.close();
}

template<class Req, class Rep>
Rep ClientEndpoint::send(IpAddress serverAddress, Port port, const Req &request)
{
    socket.send(serverAddress, port, RequestMessage(request.getType()).serialize());
    ConfirmMessage requestConfirm(socket.receive());
    socket.send(serverAddress, port, DataMessage(request.getData()).serialize());
    DataMessage replyData(socket.receive());
    socket.send(serverAddress, port, ConfirmMessage().serialize());

    return Rep(replyData.getData());
}

template OpenReply ClientEndpoint::send<OpenRequest, OpenReply>(IpAddress, Port, const OpenRequest&);
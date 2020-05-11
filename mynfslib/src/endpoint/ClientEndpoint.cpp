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
Rep ClientEndpoint::send(NetworkAddress recipient, const Req &request)
{
    socket.send(recipient, RequestMessage().serialize());
    NetworkAddress source;
    ConfirmMessage requestConfirm(socket.receive(source));
    socket.send(recipient, DataMessage(request.getType(), request.getData()).serialize());
    DataMessage replyData(socket.receive(source));
    socket.send(recipient, ConfirmMessage().serialize());

    return Rep(replyData.getData());
}

template OpenReply ClientEndpoint::send<OpenRequest, OpenReply>(NetworkAddress, const OpenRequest&);
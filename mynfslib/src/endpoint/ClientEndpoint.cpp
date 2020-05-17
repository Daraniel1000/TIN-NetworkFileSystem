#include <session/messages/ConfirmMessage.h>
#include <session/messages/DataMessage.h>
#include <session/messages/RequestMessage.h>
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
#include "ClientEndpoint.h"

ClientEndpoint::ClientEndpoint(Port port) : socket(port) {}

template<class Req, class Rep>
Rep ClientEndpoint::send(NetworkAddress recipient, const Req &request)
{
    socket.send(recipient, RequestMessage().serialize());
    NetworkAddress source{};
    ConfirmMessage requestConfirm(socket.receive(source));
    socket.send(source, DataMessage(request.getType(), request.serialize()).serialize());
    DataMessage replyData(socket.receive(source));
    socket.send(source, ConfirmMessage().serialize());

    return Rep(replyData.getData(), replyData.getError());
}

template OpenReply ClientEndpoint::send<OpenRequest, OpenReply>(NetworkAddress, const OpenRequest&);
template ReadReply ClientEndpoint::send<ReadRequest, ReadReply>(NetworkAddress, const ReadRequest&);
template WriteReply ClientEndpoint::send<WriteRequest, WriteReply>(NetworkAddress, const WriteRequest&);
template LseekReply ClientEndpoint::send<LseekRequest, LseekReply>(NetworkAddress, const LseekRequest&);
template CloseReply ClientEndpoint::send<CloseRequest, CloseReply>(NetworkAddress, const CloseRequest&);
template UnlinkReply ClientEndpoint::send<UnlinkRequest, UnlinkReply>(NetworkAddress, const UnlinkRequest&);
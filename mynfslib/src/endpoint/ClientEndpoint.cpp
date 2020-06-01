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
#include <transport/timeout_error.h>
#include <mynfslib.h>
#include <iostream>
#include <addresses/address_error.h>
#include <application/mynfs/bad_argument_error.h>
#include <transport/socket_error.h>
#include "../authentication_error.h"
#include <cstring>
#include "ClientEndpoint.h"

ClientEndpoint::ClientEndpoint(Port port) : socket(port) {}

template<class Req, class Rep>
Rep ClientEndpoint::send(NetworkAddress recipient, const Req &request) const
{
    int timeoutCount = 0;
    const int maxApproach = 5;
    const int timeout = 5;
    bool confirmation = false;

    socket.send(recipient, RequestMessage().serialize());
    NetworkAddress source{};

    while (timeoutCount < maxApproach && !confirmation)
    {
        try {
            ConfirmMessage requestConfirm(socket.receive(source, timeout));

            if(requestConfirm.getError().getErrorValue() == -1)
                throw authentication_error(1, 1,
                        "Access denied - authentication failed");
            else confirmation = true;
        }
        catch (timeout_error &e) {
            this->socket.send(recipient, RequestMessage().serialize());
            timeoutCount++;
        }
    }

    if(timeoutCount == maxApproach && !confirmation)
        throw socket_error(4, 1,
                "Host unreachable");

    timeoutCount = 0;
    socket.send(source, DataMessage(request.getType(), request.serialize()).serialize());

    while (timeoutCount < maxApproach)
    {
        try {
            DataMessage replyData(socket.receive(source, timeout));
            socket.send(source, ConfirmMessage().serialize());
            return Rep(replyData.getData(), replyData.getError());
        }
        catch (timeout_error &e) {
            socket.send(source, DataMessage(request.getType(), request.serialize()).serialize());
            timeoutCount++;
        }
    }

    throw socket_error(4, 1,
            "Host unreachable");
}

template OpenReply ClientEndpoint::send<OpenRequest, OpenReply>(NetworkAddress, const OpenRequest&) const;
template ReadReply ClientEndpoint::send<ReadRequest, ReadReply>(NetworkAddress, const ReadRequest&) const;
template WriteReply ClientEndpoint::send<WriteRequest, WriteReply>(NetworkAddress, const WriteRequest&) const;
template LseekReply ClientEndpoint::send<LseekRequest, LseekReply>(NetworkAddress, const LseekRequest&) const;
template CloseReply ClientEndpoint::send<CloseRequest, CloseReply>(NetworkAddress, const CloseRequest&) const;
template UnlinkReply ClientEndpoint::send<UnlinkRequest, UnlinkReply>(NetworkAddress, const UnlinkRequest&) const;
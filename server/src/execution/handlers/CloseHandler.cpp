#include <application/mynfs/errors/CloseReplyError.h>
#include <application/mynfs/replies/CloseReply.h>
#include <application/mynfs/requests/CloseRequest.h>
#include <unistd.h>
#include <algorithm>
#include "CloseHandler.h"


CloseHandler::CloseHandler(DomainData requestData, DomainData &replyData, PlainError &replyError) : Handler(requestData,
                                                                                                            replyData,
                                                                                                            replyError)
{
    possibleErrors.push_back(EBADF);
}

void CloseHandler::handle()
{
    CloseRequest request(this->requestData);

    auto fd = request.getDescriptor();

    int closeStatus = close(fd);

    if(closeStatus == -1) {
        int error = errno;
        if(std::find(possibleErrors.begin(), possibleErrors.end(), error) == possibleErrors.end())
            error = -1;
        CloseReply reply((CloseReplyError(error)));

        this->replyData = reply.serialize();
        this->replyError = reply.getError().serialize();
    }
    else {
        CloseReply reply((CloseReplyError(0)));

        this->replyData = reply.serialize();
        this->replyError = reply.getError().serialize();
    }
}

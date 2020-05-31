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
    // create request
    CloseRequest request(this->requestData);

    // get request data
    auto fd = request.getDescriptor();

    // do something with it here
    int closeStatus = close(fd);

    //create reply
    int error = 0;
    if(closeStatus == -1) {
        error = errno;
        if(std::find(possibleErrors.begin(), possibleErrors.end(), error) == possibleErrors.end())
            error = -1;
    }

    CloseReply reply((CloseReplyError(error)));

    this->replyData = reply.serialize();
    this->replyError = reply.getError().serialize();

}

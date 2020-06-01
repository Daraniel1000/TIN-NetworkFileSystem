#include <application/mynfs/errors/CloseReplyError.h>
#include <application/mynfs/replies/CloseReply.h>
#include <application/mynfs/requests/CloseRequest.h>
#include <unistd.h>
#include <algorithm>
#include <utility>
#include "CloseHandler.h"


CloseHandler::CloseHandler(DomainData requestData, NetworkAddress requestAddress, DomainData &replyData,
                           PlainError &replyError,
                           AccessManager &accessManager) : Handler(std::move(requestData),
                                                                   requestAddress,
                                                                   replyData,
                                                                   replyError, accessManager)
{
    possibleErrors.push_back(EBADF);
}

void CloseHandler::handle()
{
    // create request
    CloseRequest request(this->requestData);

    int error = 0;

    auto fd = this->accessManager.getSystemDescriptor(this->requestAddress.getAddress(),
                                                      request.getDescriptor());

    if (fd == -1)
        error = EBADF;
    else
    {
        // do something with it here
        int closeStatus = close(fd);

        //create reply
        if (closeStatus == -1)
        {
            error = errno;
            if (std::find(possibleErrors.begin(), possibleErrors.end(), error) == possibleErrors.end())
                error = -1;
        }
        else
            this->accessManager.clearAppDescriptor(this->requestAddress.getAddress(), request.getDescriptor());
    }
    CloseReply reply((CloseReplyError(error)));

    this->replyData = reply.serialize();
    this->replyError = reply.getError().serialize();

}

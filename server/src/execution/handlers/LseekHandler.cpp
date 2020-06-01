#include <application/mynfs/errors/LseekReplyError.h>
#include <application/mynfs/replies/LseekReply.h>
#include <application/mynfs/requests/LseekRequest.h>
#include <unistd.h>
#include <algorithm>
#include <utility>
#include "LseekHandler.h"

LseekHandler::LseekHandler(DomainData requestData, NetworkAddress requestAddress, DomainData &replyData,
                           PlainError &replyError,
                           AccessManager &accessManager) : Handler(std::move(requestData),
                                                                   requestAddress,
                                                                   replyData,
                                                                   replyError, accessManager)
{
    int errorList[] = {EBADF, EINVAL};
    possibleErrors.assign(errorList, errorList + sizeof(errorList) / sizeof(int));
}

void LseekHandler::handle()
{
    // create request
    LseekRequest request(this->requestData);

    int32_t result = 0;
    int error = 0;

    auto fd = this->accessManager.getSystemDescriptor(this->requestAddress.getAddress(),
                                                      request.getDescriptor());

    if (fd == -1)
        error = EBADF;
    else
    {
        // get request data
        auto offset = request.getOffset();
        auto whence = request.getWhence();

        // do something with it here
        result = lseek(fd, offset, whence);

        //create reply
        if (result == -1)
        {
            error = errno;
            if (std::find(possibleErrors.begin(), possibleErrors.end(), error) == possibleErrors.end())
                error = -1;
        }
    }
    LseekReply reply(result, LseekReplyError(error));

    // save reply and error
    this->replyData = reply.serialize();
    this->replyError = reply.getError().serialize();

}

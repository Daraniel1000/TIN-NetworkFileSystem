#include <application/mynfs/errors/LseekReplyError.h>
#include <application/mynfs/replies/LseekReply.h>
#include <application/mynfs/requests/LseekRequest.h>
#include <unistd.h>
#include <algorithm>
#include "LseekHandler.h"

LseekHandler::LseekHandler(DomainData requestData, DomainData &replyData, PlainError &replyError) : Handler(requestData,
                                                                                                            replyData,
                                                                                                            replyError)
{
    int errorList[] = {EBADF, EINVAL};
    possibleErrors.assign(errorList, errorList+sizeof(errorList)/sizeof(int));
}

void LseekHandler::handle()
{
    // create request
    LseekRequest request(this->requestData);

    // get request data
    auto descriptor = request.getDescriptor();
    auto offset = request.getOffset();
    auto whence = request.getWhence();

    // do something with it here
    auto result = lseek(descriptor, offset, whence);

    int error = 0;

    //create reply
    if(result == -1) {
        error = errno;
        if(std::find(possibleErrors.begin(), possibleErrors.end(), error) == possibleErrors.end())
            error = -1;
    }
    LseekReply reply(result, LseekReplyError(error));

    // save reply and error
    this->replyData = reply.serialize();
    this->replyError = reply.getError().serialize();

}

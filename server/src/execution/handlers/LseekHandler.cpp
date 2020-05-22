#include <application/mynfs/errors/LseekReplyError.h>
#include <application/mynfs/replies/LseekReply.h>
#include <application/mynfs/requests/LseekRequest.h>
#include <unistd.h>
#include "LseekHandler.h"

LseekHandler::LseekHandler(DomainData requestData, DomainData &replyData, PlainError &replyError) : Handler(requestData,
                                                                                                            replyData,
                                                                                                            replyError)
{

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

    //create reply
    if(result == -1) {
        LseekReply reply(result, LseekReplyError(errno));

        // save reply and error
        this->replyData = reply.serialize();
        this->replyError = reply.getError().serialize();
    }
    else {
        LseekReply reply(result, LseekReplyError(0));

        // save reply and error
        this->replyData = reply.serialize();
        this->replyError = reply.getError().serialize();
    }

}

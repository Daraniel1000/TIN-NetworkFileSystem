#include <application/mynfs/errors/WriteReplyError.h>
#include <application/mynfs/replies/WriteReply.h>
#include <application/mynfs/requests/WriteRequest.h>
#include <unistd.h>
#include <algorithm>
#include "WriteHandler.h"

WriteHandler::WriteHandler(DomainData requestData, DomainData &replyData, PlainError &replyError) : Handler(requestData,
                                                                                                            replyData,
                                                                                                            replyError)
{
    int errorList[] = {EBADF, EAGAIN, EFBIG, EINVAL};
    possibleErrors.assign(errorList, errorList+sizeof(errorList)/sizeof(int));
}

void WriteHandler::handle()
{
    // create request
    WriteRequest request(this->requestData);

    // get request data
    auto writeData = request.getWriteData().getData().data();
    auto descriptor = request.getDescriptor();

    // do something with it here
    int writeBytes = write(descriptor, writeData, sizeof(writeData));

    //create reply
    if(writeBytes <= 0) {
        int error = errno;
        if(std::find(possibleErrors.begin(), possibleErrors.end(), error) == possibleErrors.end())
            error = -1;
        WriteReply reply(writeBytes, WriteReplyError(errno));

        // save reply and error
        this->replyData = reply.serialize();
        this->replyError = reply.getError().serialize();
    }
    else {
        WriteReply reply(writeBytes, WriteReplyError(0));

        // save reply and error
        this->replyData = reply.serialize();
        this->replyError = reply.getError().serialize();
    }
}

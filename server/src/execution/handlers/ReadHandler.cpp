#include <application/mynfs/errors/ReadReplyError.h>
#include <application/mynfs/replies/ReadReply.h>
#include <application/mynfs/requests/ReadRequest.h>
#include <unistd.h>
#include <cstring>
#include <algorithm>
#include "ReadHandler.h"

ReadHandler::ReadHandler(DomainData requestData, DomainData &replyData, PlainError &replyError) : Handler(requestData,
                                                                                                          replyData,
                                                                                                          replyError)
{
    int errorList[] = {EBADF, EAGAIN, EINVAL, EISDIR};
    possibleErrors.assign(errorList, errorList+sizeof(errorList)/sizeof(int));
}

void ReadHandler::handle()
{
    // create request
    ReadRequest request(this->requestData);

    // get request data
    auto descriptor = request.getDescriptor();
    auto count = request.getCount();
    char* buf = (char*)malloc(count);

    // do something with it here
    auto readBytes = read(descriptor, buf, count);

    //create reply
    if(readBytes < 0) {
        int error = errno;
        if(std::find(possibleErrors.begin(), possibleErrors.end(), error) == possibleErrors.end())
            error = -1;
        ReadReply reply(buf, 0, ReadReplyError(errno)); //nie wiem
        // save reply and error
        this->replyData = reply.serialize();
        this->replyError = reply.getError().serialize();
    }
    else {
        char* data_buf = (char*)malloc(readBytes);
        memcpy(data_buf, buf, readBytes);
        ReadReply reply(data_buf, readBytes, ReadReplyError(0));

        // save reply and error
        this->replyData = reply.serialize();
        this->replyError = reply.getError().serialize();
    }
    free(buf);
}

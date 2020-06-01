#include <application/mynfs/errors/WriteReplyError.h>
#include <application/mynfs/replies/WriteReply.h>
#include <application/mynfs/requests/WriteRequest.h>
#include <unistd.h>
#include <algorithm>
#include <utility>
#include "WriteHandler.h"

WriteHandler::WriteHandler(DomainData requestData, NetworkAddress requestAddress, DomainData &replyData,
                           PlainError &replyError,
                           AccessManager &accessManager) : Handler(std::move(requestData),
                                                                   requestAddress,
                                                                   replyData,
                                                                   replyError, accessManager)
{
    int errorList[] = {EBADF, EAGAIN, EFBIG, EINVAL};
    possibleErrors.assign(errorList, errorList + sizeof(errorList) / sizeof(int));
}

void WriteHandler::handle()
{
    // create request
    WriteRequest request(this->requestData);

    int writeBytes = 0;
    int error = 0;

    auto fd = this->accessManager.getSystemDescriptor(this->requestAddress.getAddress(),
                                                      request.getDescriptor());

    if (fd == -1)
        error = EBADF;
    else
    {
        // get request data
        auto writeData = request.getWriteData().getData().data();

        // do something with it here
        writeBytes = write(fd, writeData, request.getWriteData().getData().size());

        //create reply
        if (writeBytes <= 0)
        {
            error = errno;
            if (std::find(possibleErrors.begin(), possibleErrors.end(), error) == possibleErrors.end())
                error = -1;
        }
    }
    WriteReply reply(writeBytes, WriteReplyError(error));

    // save reply and error
    this->replyData = reply.serialize();
    this->replyError = reply.getError().serialize();

}

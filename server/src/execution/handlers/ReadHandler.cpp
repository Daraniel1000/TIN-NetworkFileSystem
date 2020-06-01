#include <application/mynfs/errors/ReadReplyError.h>
#include <application/mynfs/replies/ReadReply.h>
#include <application/mynfs/requests/ReadRequest.h>
#include <unistd.h>
#include <cstring>
#include <algorithm>
#include <utility>
#include "ReadHandler.h"

ReadHandler::ReadHandler(DomainData requestData, NetworkAddress requestAddress, DomainData &replyData,
                         PlainError &replyError,
                         AccessManager &accessManager) : Handler(std::move(requestData),
                                                                 requestAddress,
                                                                 replyData,
                                                                 replyError,
                                                                 accessManager)
{
    int errorList[] = {EBADF, EAGAIN, EINVAL, EISDIR};
    possibleErrors.assign(errorList, errorList + sizeof(errorList) / sizeof(int));
}

void ReadHandler::handle()
{
    // create request
    ReadRequest request(this->requestData);

    int error = 0;
    auto readBytes = 0;
    auto *buf = (std::byte *) malloc(request.getCount());

    auto fd = this->accessManager.getSystemDescriptor(this->requestAddress.getAddress(),
                                                      request.getDescriptor());

    if (fd == -1)
        error = EBADF;
    else
    {
        auto count = request.getCount();

        // do something with it here
        readBytes = read(fd, buf, count);

        //create reply
        if (readBytes < 0)
        {
            error = errno;
            if (std::find(possibleErrors.begin(), possibleErrors.end(), error) == possibleErrors.end())
                error = -1;
            readBytes = 0;
        }
    }
    ReadReply reply(buf, readBytes, ReadReplyError(error));

    // save reply and error
    this->replyData = reply.serialize();
    this->replyError = reply.getError().serialize();
    free(buf);
}

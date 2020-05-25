#include <application/mynfs/errors/UnlinkReplyError.h>
#include <application/mynfs/replies/UnlinkReply.h>
#include <application/mynfs/requests/UnlinkRequest.h>
#include <unistd.h>
#include <algorithm>
#include "UnlinkHandler.h"

UnlinkHandler::UnlinkHandler(DomainData requestData, DomainData &replyData, PlainError &replyError) : Handler(
        requestData, replyData, replyError)
{
    int errorList[] = {EISDIR, EBUSY, ENAMETOOLONG, ENOENT, ENOTDIR};
    possibleErrors.assign(errorList, errorList+sizeof(errorList)/sizeof(int));
}

void UnlinkHandler::handle()
{
    // create request
    UnlinkRequest request(this->requestData);

    // get request data
    const char* path = request.getPath().data();

    // do something with it here
    int result = unlink(path);

    //create reply
    if(result == -1) {
        int error = errno;
        if(std::find(possibleErrors.begin(), possibleErrors.end(), error) == possibleErrors.end())
            error = -1;
        UnlinkReply reply((UnlinkReplyError(errno)));

        // save reply and error
        this->replyData = reply.serialize();
        this->replyError = reply.getError().serialize();
    }
    else {
        UnlinkReply reply(UnlinkReplyError(0));

        // save reply and error
        this->replyData = reply.serialize();
        this->replyError = reply.getError().serialize();
    }
}

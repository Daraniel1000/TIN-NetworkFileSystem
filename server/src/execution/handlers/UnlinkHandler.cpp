#include <application/mynfs/errors/UnlinkReplyError.h>
#include <application/mynfs/replies/UnlinkReply.h>
#include <application/mynfs/requests/UnlinkRequest.h>
#include <unistd.h>
#include <algorithm>
#include <utility>
#include "UnlinkHandler.h"

UnlinkHandler::UnlinkHandler(DomainData requestData, NetworkAddress requestAddress, DomainData &replyData,
                             PlainError &replyError,
                             AccessManager &accessManager) : Handler(
        std::move(requestData), requestAddress, replyData, replyError, accessManager)
{
    int errorList[] = {EISDIR, EBUSY, ENAMETOOLONG, ENOENT, ENOTDIR};
    possibleErrors.assign(errorList, errorList + sizeof(errorList) / sizeof(int));
}

void UnlinkHandler::handle()
{
    int error = 0;
    // create request
    UnlinkRequest request(this->requestData);

    if (!this->accessManager.isPathPermitted(request.getPath()))
        error = EACCES;
    else
    {
        // get request data
        auto pathStr = (this->accessManager.getFsPath() + "/" + request.getPath());
        const char *path = pathStr.data();

        // do something with it here
        int result = unlink(path);

        //create reply
        if (result == -1)
        {
            error = errno;
            if (std::find(possibleErrors.begin(), possibleErrors.end(), error) == possibleErrors.end())
                error = -1;
        }
    }
    UnlinkReply reply((UnlinkReplyError(error)));

    // save reply and error
    this->replyData = reply.serialize();
    this->replyError = reply.getError().serialize();

}

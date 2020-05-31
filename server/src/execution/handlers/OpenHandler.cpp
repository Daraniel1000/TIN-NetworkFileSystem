#include <application/mynfs/errors/OpenReplyError.h>
#include <application/mynfs/replies/OpenReply.h>
#include <application/mynfs/requests/OpenRequest.h>
#include <fcntl.h>
#include <algorithm>
#include "OpenHandler.h"

OpenHandler::OpenHandler(DomainData requestData, DomainData &replyData, PlainError &replyError) : Handler(requestData,
                                                                                                       replyData,
                                                                                                       replyError)
{
    int errorList[] = {EACCES, EEXIST, ELOOP, ENAMETOOLONG, ENFILE, ENOENT, ENOSPC, ENOTDIR, EINVAL};
    possibleErrors.assign(errorList, errorList+sizeof(errorList)/sizeof(int));
}


void OpenHandler::handle()
{
    // create request
    OpenRequest request(this->requestData);

    // get request data
    const char* path = request.getPath().data();
    auto oflag = request.getOflag();

    // do something with it here
    int fd = open(path,oflag, 0777);

    //create reply
    int error = 0;
    if(fd == -1) {
        error = errno;
        if (std::find(possibleErrors.begin(), possibleErrors.end(), error) == possibleErrors.end())
            error = -1;
    }
    OpenReply reply(fd, OpenReplyError(error));

    // save reply and error
    this->replyData = reply.serialize();
    this->replyError = reply.getError().serialize();

}

OpenHandler::~OpenHandler() {

}


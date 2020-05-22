#include <application/mynfs/errors/OpenReplyError.h>
#include <application/mynfs/replies/OpenReply.h>
#include <application/mynfs/requests/OpenRequest.h>
#include <fcntl.h>
#include "OpenHandler.h"

OpenHandler::OpenHandler(DomainData requestData, DomainData &replyData, PlainError &replyError) : Handler(requestData,
                                                                                                       replyData,
                                                                                                       replyError)
{

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
    if(fd == -1) {
        OpenReply reply(fd, OpenReplyError(errno));

        // save reply and error
        this->replyData = reply.serialize();
        this->replyError = reply.getError().serialize();
    }
    else {
        OpenReply reply(fd, OpenReplyError(0));

        // save reply and error
        this->replyData = reply.serialize();
        this->replyError = reply.getError().serialize();
    }
}

OpenHandler::~OpenHandler() {

}


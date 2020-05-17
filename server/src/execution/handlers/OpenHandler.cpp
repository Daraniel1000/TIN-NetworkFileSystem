#include <application/mynfs/errors/OpenReplyError.h>
#include <application/mynfs/replies/OpenReply.h>
#include <application/mynfs/requests/OpenRequest.h>
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
    auto path = request.getPath();
    auto oflag = request.getOflag();

    // do something with it here
    true;

    //create reply
    OpenReply reply(3, OpenReplyError(0));

    // save reply and error
    this->replyData = reply.serialize();
    this->replyError = reply.getError().serialize();
}

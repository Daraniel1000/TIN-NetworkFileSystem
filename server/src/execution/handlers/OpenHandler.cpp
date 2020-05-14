#include <application/mynfs/errors/OpenReplyError.h>
#include <application/mynfs/replies/OpenReply.h>
#include "OpenHandler.h"

OpenHandler::OpenHandler(DomainData requestData, DomainData &replyData, PlainError &replyError) : Handler(requestData,
                                                                                                       replyData,
                                                                                                       replyError)
{

}

void OpenHandler::handle()
{
    OpenReply reply(3, OpenReplyError(0));

    this->replyData = reply.getData();
    this->replyError = reply.getError().serialize();
}

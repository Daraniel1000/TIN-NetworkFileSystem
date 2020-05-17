#ifndef MYNFS_READHANDLER_H
#define MYNFS_READHANDLER_H


#include "Handler.h"

class ReadHandler : public Handler
{
public:
    ReadHandler(DomainData requestData, DomainData& replyData, PlainError& replyError);
    void handle() override;
};

#endif //MYNFS_READHANDLER_H

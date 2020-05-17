#ifndef MYNFS_WRITEHANDLER_H
#define MYNFS_WRITEHANDLER_H


#include "Handler.h"

class WriteHandler : public Handler
{
public:
    WriteHandler(DomainData requestData, DomainData& replyData, PlainError& replyError);
    void handle() override;
};


#endif //MYNFS_WRITEHANDLER_H

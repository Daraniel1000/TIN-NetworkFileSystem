#ifndef MYNFS_CLOSEHANDLER_H
#define MYNFS_CLOSEHANDLER_H


#include "Handler.h"

class CloseHandler : public Handler
{
public:
    CloseHandler(DomainData requestData, DomainData& replyData, PlainError& replyError);
    void handle() override;
};

#endif //MYNFS_CLOSEHANDLER_H

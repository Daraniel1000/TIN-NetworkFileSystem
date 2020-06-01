#ifndef MYNFS_CLOSEHANDLER_H
#define MYNFS_CLOSEHANDLER_H


#include "Handler.h"

class CloseHandler : public Handler
{
public:
    CloseHandler(DomainData requestData, NetworkAddress requestAddress, DomainData &replyData, PlainError &replyError,
                 AccessManager &accessManager);

    void handle() override;

private:
    std::vector<int> possibleErrors;
};

#endif //MYNFS_CLOSEHANDLER_H

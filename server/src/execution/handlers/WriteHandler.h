#ifndef MYNFS_WRITEHANDLER_H
#define MYNFS_WRITEHANDLER_H


#include "Handler.h"

class WriteHandler : public Handler
{
public:
    WriteHandler(DomainData requestData, NetworkAddress requestAddress, DomainData &replyData, PlainError &replyError,
                 AccessManager &accessManager);

    void handle() override;

private:
    std::vector<int> possibleErrors;
};


#endif //MYNFS_WRITEHANDLER_H

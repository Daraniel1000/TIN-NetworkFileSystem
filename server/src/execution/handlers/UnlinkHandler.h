#ifndef MYNFS_UNLINKHANDLER_H
#define MYNFS_UNLINKHANDLER_H


#include "Handler.h"

class UnlinkHandler : public Handler
{
public:
    UnlinkHandler(DomainData requestData, NetworkAddress requestAddress, DomainData &replyData, PlainError &replyError,
                  AccessManager &accessManager);

    void handle() override;

private:
    std::vector<int> possibleErrors;
};


#endif //MYNFS_UNLINKHANDLER_H

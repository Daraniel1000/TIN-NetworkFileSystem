#ifndef MYNFS_UNLINKHANDLER_H
#define MYNFS_UNLINKHANDLER_H


#include "Handler.h"

class UnlinkHandler : public Handler
{
public:
    UnlinkHandler(DomainData requestData, DomainData& replyData, PlainError& replyError);
    void handle() override;

private:
    std::vector<int> possibleErrors;
};


#endif //MYNFS_UNLINKHANDLER_H

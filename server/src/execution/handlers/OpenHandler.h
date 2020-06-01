#ifndef MYNFS_OPENHANDLER_H
#define MYNFS_OPENHANDLER_H


#include "Handler.h"

class OpenHandler : public Handler
{
public:
    OpenHandler(DomainData requestData, NetworkAddress requestAddress, DomainData &replyData, PlainError &replyError,
                AccessManager &accessManager);

    void handle() override;

    virtual ~OpenHandler();

private:
    std::vector<int> possibleErrors;
};


#endif //MYNFS_OPENHANDLER_H

#ifndef MYNFS_OPENHANDLER_H
#define MYNFS_OPENHANDLER_H


#include "Handler.h"

class OpenHandler : public Handler
{
public:
    OpenHandler(DomainData requestData, DomainData& replyData, PlainError& replyError);
    void handle() override;

    virtual ~OpenHandler();

private:
    std::vector<int> possibleErrors;
};


#endif //MYNFS_OPENHANDLER_H

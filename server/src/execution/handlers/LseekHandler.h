#ifndef MYNFS_LSEEKHANDLER_H
#define MYNFS_LSEEKHANDLER_H


#include "Handler.h"

class LseekHandler : public Handler
{
public:
    LseekHandler(DomainData requestData, DomainData& replyData, PlainError& replyError);
    void handle() override;
private:
    std::vector<int> possibleErrors;
};


#endif //MYNFS_LSEEKHANDLER_H

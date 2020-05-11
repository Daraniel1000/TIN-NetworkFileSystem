#ifndef MYNFS_HANDLER_H
#define MYNFS_HANDLER_H


#include <session/DomainData.h>

class Handler
{
    DomainData requestData;
    DomainData& replyData;
public:
    Handler(DomainData requestData, DomainData& replyData) : requestData(requestData), replyData(replyData) {}
    virtual ~Handler() = default;

    virtual void handle() = 0;
};


#endif //MYNFS_HANDLER_H

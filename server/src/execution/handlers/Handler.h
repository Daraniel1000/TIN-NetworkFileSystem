#ifndef MYNFS_HANDLER_H
#define MYNFS_HANDLER_H


#include <cstdint>
#include <session/DomainData.h>

class Handler
{
    DomainData requestData;
    DomainData &replyData;
    int8_t &replyError;
public:
    Handler(DomainData requestData, DomainData &replyData, int8_t &replyError) : requestData(requestData),
                                                                                 replyData(replyData),
                                                                                 replyError(replyError)
    {}

    virtual ~Handler() = default;

    virtual void handle() = 0;
};


#endif //MYNFS_HANDLER_H

#ifndef MYNFS_LSEEKHANDLERFACTORY_H
#define MYNFS_LSEEKHANDLERFACTORY_H


#include "HandlerFactory.h"
#include "../handlers/LseekHandler.h"

class LseekHandlerFactory : public HandlerFactory
{
public:
    std::unique_ptr<Handler> create(DomainData requestData, DomainData &replyData, PlainError& replyError) const override
    {
        return std::make_unique<LseekHandler>(requestData, replyData, replyError);
    }
};


#endif //MYNFS_LSEEKHANDLERFACTORY_H

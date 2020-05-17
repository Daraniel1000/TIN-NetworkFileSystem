#ifndef MYNFS_CLOSEHANDLERFACTORY_H
#define MYNFS_CLOSEHANDLERFACTORY_H


#include "HandlerFactory.h"
#include "../handlers/CloseHandler.h"

class CloseHandlerFactory : public HandlerFactory
{
public:
    std::unique_ptr<Handler> create(DomainData requestData, DomainData &replyData, PlainError& replyError) const override
    {
        return std::make_unique<CloseHandler>(requestData, replyData, replyError);
    }
};


#endif //MYNFS_CLOSEHANDLERFACTORY_H

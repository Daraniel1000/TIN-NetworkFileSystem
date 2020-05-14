#ifndef MYNFS_OPENHANDLERFACTORY_H
#define MYNFS_OPENHANDLERFACTORY_H


#include "HandlerFactory.h"
#include "../handlers/OpenHandler.h"

class OpenHandlerFactory : public HandlerFactory
{
public:
    std::unique_ptr<Handler> create(DomainData requestData, DomainData &replyData, PlainError& replyError) const override
    {
        return std::make_unique<OpenHandler>(requestData, replyData, replyError);
    }
};


#endif //MYNFS_OPENHANDLERFACTORY_H

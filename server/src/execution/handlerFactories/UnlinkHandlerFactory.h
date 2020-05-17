#ifndef MYNFS_UNLINKHANDLERFACTORY_H
#define MYNFS_UNLINKHANDLERFACTORY_H


#include "HandlerFactory.h"
#include "../handlers/UnlinkHandler.h"

class UnlinkHandlerFactory : public HandlerFactory
{
public:
    std::unique_ptr<Handler> create(DomainData requestData, DomainData &replyData, PlainError& replyError) const override
    {
        return std::make_unique<UnlinkHandler>(requestData, replyData, replyError);
    }
};


#endif //MYNFS_UNLINKHANDLERFACTORY_H

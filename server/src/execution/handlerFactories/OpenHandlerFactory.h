#ifndef MYNFS_OPENHANDLERFACTORY_H
#define MYNFS_OPENHANDLERFACTORY_H


#include "HandlerFactory.h"
#include "../handlers/OpenHandler.h"

class OpenHandlerFactory : public HandlerFactory
{
public:
    std::unique_ptr<Handler>
    create(DomainData requestData, NetworkAddress requestAddress, DomainData &replyData, PlainError &replyError,
           AccessManager &accessManager) const override
    {
        return std::make_unique<OpenHandler>(requestData, requestAddress, replyData, replyError, accessManager);
    }
};


#endif //MYNFS_OPENHANDLERFACTORY_H

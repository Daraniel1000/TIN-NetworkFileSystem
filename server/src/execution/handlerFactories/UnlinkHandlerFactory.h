#ifndef MYNFS_UNLINKHANDLERFACTORY_H
#define MYNFS_UNLINKHANDLERFACTORY_H


#include "HandlerFactory.h"
#include "../handlers/UnlinkHandler.h"

class UnlinkHandlerFactory : public HandlerFactory
{
public:
    std::unique_ptr<Handler>
    create(DomainData requestData, NetworkAddress requestAddress, DomainData &replyData, PlainError &replyError,
           AccessManager &accessManager) const override
    {
        return std::make_unique<UnlinkHandler>(requestData, requestAddress, replyData, replyError, accessManager);
    }
};


#endif //MYNFS_UNLINKHANDLERFACTORY_H

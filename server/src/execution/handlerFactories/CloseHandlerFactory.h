#ifndef MYNFS_CLOSEHANDLERFACTORY_H
#define MYNFS_CLOSEHANDLERFACTORY_H


#include "HandlerFactory.h"
#include "../handlers/CloseHandler.h"

class CloseHandlerFactory : public HandlerFactory
{
public:
    std::unique_ptr<Handler>
    create(DomainData requestData, NetworkAddress requestAddress, DomainData &replyData, PlainError &replyError,
           AccessManager &accessManager) const override
    {
        return std::make_unique<CloseHandler>(requestData, requestAddress, replyData, replyError, accessManager);
    }
};


#endif //MYNFS_CLOSEHANDLERFACTORY_H

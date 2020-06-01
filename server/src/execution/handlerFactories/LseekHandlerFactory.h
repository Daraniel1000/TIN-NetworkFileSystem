#ifndef MYNFS_LSEEKHANDLERFACTORY_H
#define MYNFS_LSEEKHANDLERFACTORY_H


#include "HandlerFactory.h"
#include "../handlers/LseekHandler.h"

class LseekHandlerFactory : public HandlerFactory
{
public:
    std::unique_ptr<Handler>
    create(DomainData requestData, NetworkAddress requestAddress, DomainData &replyData, PlainError &replyError,
           AccessManager &accessManager) const override
    {
        return std::make_unique<LseekHandler>(requestData, requestAddress, replyData, replyError, accessManager);
    }
};


#endif //MYNFS_LSEEKHANDLERFACTORY_H

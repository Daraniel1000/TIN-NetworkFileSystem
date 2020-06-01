#ifndef MYNFS_WRITEHANDLERFACTORY_H
#define MYNFS_WRITEHANDLERFACTORY_H


#include "HandlerFactory.h"
#include "../handlers/WriteHandler.h"

class WriteHandlerFactory : public HandlerFactory
{
public:
    std::unique_ptr<Handler>
    create(DomainData requestData, NetworkAddress requestAddress, DomainData &replyData, PlainError &replyError,
           AccessManager &accessManager) const override
    {
        return std::make_unique<WriteHandler>(requestData, requestAddress, replyData, replyError, accessManager);
    }
};


#endif //MYNFS_WRITEHANDLERFACTORY_H

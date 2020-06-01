#ifndef MYNFS_READHANDLERFACTORY_H
#define MYNFS_READHANDLERFACTORY_H


#include "HandlerFactory.h"
#include "../handlers/ReadHandler.h"

class ReadHandlerFactory : public HandlerFactory
{
public:
    std::unique_ptr<Handler> create(DomainData requestData, NetworkAddress requestAddress, DomainData &replyData,
                                    PlainError &replyError, AccessManager &accessManager) const override
    {
        return std::make_unique<ReadHandler>(requestData, requestAddress, replyData, replyError, accessManager);
    }
};


#endif //MYNFS_READHANDLERFACTORY_H

#ifndef MYNFS_READHANDLERFACTORY_H
#define MYNFS_READHANDLERFACTORY_H


#include "HandlerFactory.h"
#include "../handlers/ReadHandler.h"

class ReadHandlerFactory : public HandlerFactory
{
public:
    std::unique_ptr<Handler> create(DomainData requestData, DomainData &replyData, PlainError& replyError) const override
    {
        return std::make_unique<ReadHandler>(requestData, replyData, replyError);
    }
};


#endif //MYNFS_READHANDLERFACTORY_H

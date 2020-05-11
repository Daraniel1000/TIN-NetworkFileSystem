#ifndef MYNFS_HANDLERFACTORY_H
#define MYNFS_HANDLERFACTORY_H


#include "../handlers/Handler.h"

class HandlerFactory
{
public:
    virtual ~HandlerFactory() = default;

    virtual std::unique_ptr<Handler> create(DomainData requestData, DomainData& replyData) const = 0;
};


#endif //MYNFS_HANDLERFACTORY_H

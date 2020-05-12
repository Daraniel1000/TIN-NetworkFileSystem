#ifndef MYNFS_HANDLERFACTORY_H
#define MYNFS_HANDLERFACTORY_H


#include "../handlers/Handler.h"

class HandlerFactory
{
public:
    virtual ~HandlerFactory() = default;

    /**
     * Create new handler object and return pointer to it
     * Returned pointer is std::unique_ptr so the object will be AUTOMATICALLY deleted when it goes out of scope
     * Parameters are simply passed to the handler
     */
    virtual std::unique_ptr<Handler> create(DomainData requestData, DomainData& replyData, int8_t& replyError) const = 0;
};


#endif //MYNFS_HANDLERFACTORY_H

#ifndef MYNFS_HANDLERFACTORYPOOL_H
#define MYNFS_HANDLERFACTORYPOOL_H


#include <map>
#include <memory>
#include "handlerFactories/HandlerFactory.h"

class HandlerFactoryPool
{
    std::map<uint8_t , std::unique_ptr<HandlerFactory>> handlersFactories;

public:
    HandlerFactoryPool();

    /**
     * Get handler factory of given type
     */
    const HandlerFactory& getHandlerFactory(uint8_t type) const;
};


#endif //MYNFS_HANDLERFACTORYPOOL_H

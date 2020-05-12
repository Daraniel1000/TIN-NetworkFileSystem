#ifndef MYNFS_HANDLERFACTORYPOOL_H
#define MYNFS_HANDLERFACTORYPOOL_H


#include <map>
#include <memory>
#include "handlerFactories/HandlerFactory.h"

class HandlerFactoryPool
{
    std::map<int8_t , std::unique_ptr<HandlerFactory>> handlersFactories;

public:
    HandlerFactoryPool();

    /**
     * Get handler factory of given type
     */
    const HandlerFactory& getHandlerFactory(int8_t type) const;
};


#endif //MYNFS_HANDLERFACTORYPOOL_H

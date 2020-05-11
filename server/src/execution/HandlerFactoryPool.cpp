#include "HandlerFactoryPool.h"
#include "handlerFactories/OpenHandlerFactory.h"

HandlerFactoryPool::HandlerFactoryPool()
{
    this->handlersFactories[0] = std::make_unique<OpenHandlerFactory>();
}

const HandlerFactory &HandlerFactoryPool::getHandlerFactory(int8_t type) const
{
    return *this->handlersFactories.at(type);
}

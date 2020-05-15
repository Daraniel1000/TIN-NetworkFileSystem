#include "HandlerFactoryPool.h"
#include "handlerFactories/OpenHandlerFactory.h"

#include "application/mynfs/requests/OpenRequest.h"

HandlerFactoryPool::HandlerFactoryPool()
{
    this->handlersFactories[OpenRequest::TYPE] = std::make_unique<OpenHandlerFactory>();
}

const HandlerFactory &HandlerFactoryPool::getHandlerFactory(uint8_t type) const
{
    return *this->handlersFactories.at(type);
}

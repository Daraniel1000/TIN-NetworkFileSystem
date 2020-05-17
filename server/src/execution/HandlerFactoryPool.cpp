#include "HandlerFactoryPool.h"
#include "handlerFactories/OpenHandlerFactory.h"
#include "handlerFactories/ReadHandlerFactory.h"
#include "handlerFactories/WriteHandlerFactory.h"
#include "handlerFactories/LseekHandlerFactory.h"
#include "handlerFactories/CloseHandlerFactory.h"
#include "handlerFactories/UnlinkHandlerFactory.h"

#include "application/mynfs/requests/OpenRequest.h"
#include "application/mynfs/requests/ReadRequest.h"
#include "application/mynfs/requests/WriteRequest.h"
#include "application/mynfs/requests/LseekRequest.h"
#include "application/mynfs/requests/CloseRequest.h"
#include "application/mynfs/requests/UnlinkRequest.h"

HandlerFactoryPool::HandlerFactoryPool()
{
    this->handlersFactories[OpenRequest::TYPE] = std::make_unique<OpenHandlerFactory>();
    this->handlersFactories[ReadRequest::TYPE] = std::make_unique<ReadHandlerFactory>();
    this->handlersFactories[WriteRequest::TYPE] = std::make_unique<WriteHandlerFactory>();
    this->handlersFactories[LseekRequest::TYPE] = std::make_unique<LseekHandlerFactory>();
    this->handlersFactories[CloseRequest::TYPE] = std::make_unique<CloseHandlerFactory>();
    this->handlersFactories[UnlinkRequest::TYPE] = std::make_unique<UnlinkHandlerFactory>();
}

const HandlerFactory &HandlerFactoryPool::getHandlerFactory(uint8_t type) const
{
    return *this->handlersFactories.at(type);
}

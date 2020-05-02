#include "messages/RequestMessage.h"

RequestMessage::RequestMessage(int8_t type) : type(type)
{}

RequestMessage::RequestMessage(PlainData data)
{}

int8_t RequestMessage::getType() const
{
    return this->type;
}


PlainData RequestMessage::serialize()
{
    return PlainData();
}
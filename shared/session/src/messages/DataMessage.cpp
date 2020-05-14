#include "session/messages/DataMessage.h"

DataMessage::DataMessage(int8_t type, DomainData data, PlainError error)
{

}

DataMessage::DataMessage(PlainData data)
{

}

int8_t DataMessage::getType()
{
    return this->type;
}

PlainError DataMessage::getError()
{
    return this->error;
}

DomainData DataMessage::getData()
{
    return this->data;
}

PlainData DataMessage::serialize()
{
    return PlainData();
}
#include "session/messages/DataMessage.h"

DataMessage::DataMessage(int8_t type, DomainData data)
{

}

DataMessage::DataMessage(PlainData data)
{

}

int8_t DataMessage::getType()
{
    return this->type;
}

DomainData DataMessage::getData()
{
    return this->data;
}

PlainData DataMessage::serialize()
{
    return PlainData();
}
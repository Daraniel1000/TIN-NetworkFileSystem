#include "session/messages/DataMessage.h"

DataMessage::DataMessage(DomainData data)
{

}

DataMessage::DataMessage(PlainData data)
{

}

DomainData DataMessage::getData()
{
    return this->data;
}

PlainData DataMessage::serialize()
{
    return PlainData();
}
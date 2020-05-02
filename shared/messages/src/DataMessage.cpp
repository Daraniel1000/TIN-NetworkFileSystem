#include "messages/DataMessage.h"

DataMessage::DataMessage(DomainData data)
{

}

DataMessage::DataMessage(PlainData data)
{

}

PlainData DataMessage::serialize()
{
    return PlainData();
}
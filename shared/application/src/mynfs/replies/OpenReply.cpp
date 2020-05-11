#include "application/mynfs/replies/OpenReply.h"

OpenReply::OpenReply(int16_t descriptor, int8_t error) : Reply(error)
{

}


OpenReply::OpenReply(DomainData data, int8_t error) : Reply(error)
{

}

int16_t OpenReply::getDescriptor()
{
    return this->descriptor;
}

int8_t OpenReply::getError()
{
    return 0;
}

DomainData OpenReply::getData() const
{
    return DomainData();
}

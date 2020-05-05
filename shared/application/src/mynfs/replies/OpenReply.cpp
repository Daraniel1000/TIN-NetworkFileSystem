#include "application/mynfs/replies/OpenReply.h"

OpenReply::OpenReply(DomainData data)
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

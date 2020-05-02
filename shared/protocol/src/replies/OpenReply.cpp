#include "protocol/replies/OpenReply.h"

OpenReply::OpenReply(DataMessage dataMessage)
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

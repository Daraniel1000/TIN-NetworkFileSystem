#include "application/mynfs/replies/OpenReply.h"

#include <utility>

OpenReply::OpenReply(int16_t descriptor, OpenReplyError error) : descriptor(descriptor), error(std::move(error)) {}

OpenReply::OpenReply(DomainData data, PlainError error)
{

}

int16_t OpenReply::getDescriptor()
{
    return this->descriptor;
}

const MyNFSError &OpenReply::getError()
{
    return this->error;
}

DomainData OpenReply::getData() const
{
    return DomainData();
}

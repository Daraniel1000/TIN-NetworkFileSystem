#include "application/mynfs/replies/CloseReply.h"

CloseReply::CloseReply(CloseReplyError error)
{

}

CloseReply::CloseReply(const DomainData &data, PlainError error)
{

}

const MyNFSError &CloseReply::getError() const
{
    return this->error;
}

DomainData CloseReply::serialize() const
{
    return DomainData();
}

bool CloseReply::operator==(const CloseReply &rhs) const
{
    return error == rhs.error;
}

bool CloseReply::operator!=(const CloseReply &rhs) const
{
    return !(rhs == *this);
}

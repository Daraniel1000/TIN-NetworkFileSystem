#include "application/mynfs/replies/UnlinkReply.h"

UnlinkReply::UnlinkReply(UnlinkReplyError error)
{

}

UnlinkReply::UnlinkReply(const DomainData &data, PlainError error)
{

}

const MyNFSError &UnlinkReply::getError() const
{
    return this->error;
}

DomainData UnlinkReply::serialize() const
{
    return DomainData();
}

bool UnlinkReply::operator==(const UnlinkReply &rhs) const
{
    return error == rhs.error;
}

bool UnlinkReply::operator!=(const UnlinkReply &rhs) const
{
    return !(rhs == *this);
}

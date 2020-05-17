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

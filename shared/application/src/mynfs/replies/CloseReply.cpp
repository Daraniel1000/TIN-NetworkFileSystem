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

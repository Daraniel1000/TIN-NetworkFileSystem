#include "application/mynfs/replies/WriteReply.h"

WriteReply::WriteReply(int16_t count, WriteReplyError error)
{

}

WriteReply::WriteReply(const DomainData &data, PlainError error)
{

}

int16_t WriteReply::getCount() const
{
    return 0;
}

const MyNFSError &WriteReply::getError() const
{
    return this->error;
}

DomainData WriteReply::serialize() const
{
    return DomainData();
}
#include "application/mynfs/replies/ReadReply.h"

ReadReply::ReadReply(void const *buf, int16_t count, ReadReplyError error)
{

}

ReadReply::ReadReply(const DomainData &data, PlainError error)
{

}

const PlainData &ReadReply::getData() const
{
    return this->readData;
}

const MyNFSError &ReadReply::getError() const
{
    return this->error;
}

DomainData ReadReply::serialize() const
{
    return DomainData();
}

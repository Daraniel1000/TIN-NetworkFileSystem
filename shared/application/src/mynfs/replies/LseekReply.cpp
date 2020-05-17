#include "application/mynfs/replies/LseekReply.h"

LseekReply::LseekReply(int32_t offset, LseekReplyError error)
{

}

LseekReply::LseekReply(const DomainData &data, PlainError error)
{

}

int32_t LseekReply::getOffset() const
{
    return 0;
}

const MyNFSError &LseekReply::getError() const
{
    return this->error;
}

DomainData LseekReply::serialize() const
{
    return DomainData();
}

bool LseekReply::operator==(const LseekReply &rhs) const
{
    return offset == rhs.offset &&
           error == rhs.error;
}

bool LseekReply::operator!=(const LseekReply &rhs) const
{
    return !(rhs == *this);
}

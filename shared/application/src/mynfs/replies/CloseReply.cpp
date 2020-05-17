#include "application/mynfs/replies/CloseReply.h"

CloseReply::CloseReply(CloseReplyError error) : error(std::move(error)) {}

CloseReply::CloseReply(const DomainData &data, PlainError error) : error(std::move(error))
{
    auto expectedSize = 0;
    if (data.getSize() != expectedSize)
        throw std::logic_error(
                "Bad message size. Expected " + std::to_string(expectedSize) + ", but got " +
                std::to_string(data.getSize()));
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

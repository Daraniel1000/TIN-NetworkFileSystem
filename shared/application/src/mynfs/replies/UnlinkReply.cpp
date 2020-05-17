#include "application/mynfs/replies/UnlinkReply.h"

UnlinkReply::UnlinkReply(UnlinkReplyError error) : error(std::move(error))
{}

UnlinkReply::UnlinkReply(const DomainData &data, PlainError error) : error(std::move(error))
{
    auto expectedSize = 0;
    if (data.getSize() != expectedSize)
        throw std::logic_error(
                "Bad message size. Expected " + std::to_string(expectedSize) + ", but got " +
                std::to_string(data.getSize()));
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

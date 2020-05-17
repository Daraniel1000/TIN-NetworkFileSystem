#include <session/Converter.h>
#include "application/mynfs/replies/LseekReply.h"

LseekReply::LseekReply(int32_t offset, LseekReplyError error) : offset(offset), error(std::move(error))
{}

LseekReply::LseekReply(const DomainData &data, PlainError error) : error(std::move(error))
{
    auto expectedSize = sizeof(this->offset);
    if (data.getSize() != expectedSize)
        throw std::logic_error(
                "Bad message size. Expected " + std::to_string(expectedSize) + ", but got " +
                std::to_string(data.getSize()));

    //get offset
    this->offset = Converter::getInt32FromBytes(
            data.getNBytes(sizeof(this->offset)));
}

int32_t LseekReply::getOffset() const
{
    return this->offset;
}

const MyNFSError &LseekReply::getError() const
{
    return this->error;
}

DomainData LseekReply::serialize() const
{
    // convert offset
    std::vector<std::byte> dataBytes = Converter::getBytesFromInt32(this->offset);

    return DomainData(dataBytes);
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

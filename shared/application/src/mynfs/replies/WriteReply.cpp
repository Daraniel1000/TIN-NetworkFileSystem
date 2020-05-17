#include <session/Converter.h>
#include "application/mynfs/replies/WriteReply.h"

const int16_t WriteReply::MAX_DATA_SIZE = 4096;

WriteReply::WriteReply(int16_t count, WriteReplyError error) : count(count), error(std::move(error))
{
    if (this->count > WriteReply::MAX_DATA_SIZE)
        throw std::logic_error(
                "Count is too big. Expected at most" + std::to_string(WriteReply::MAX_DATA_SIZE) + ", but got " +
                std::to_string(this->count));
}

WriteReply::WriteReply(const DomainData &data, PlainError error) : error(std::move(error))
{
    auto expectedSize = sizeof(this->count);
    if (data.getSize() != expectedSize)
        throw std::logic_error(
                "Bad message size. Expected " + std::to_string(expectedSize) + ", but got " +
                std::to_string(data.getSize()));

    //get descriptor
    this->count = Converter::getInt16FromBytes(
            data.getNBytes(sizeof(this->count)));

    if (this->count > WriteReply::MAX_DATA_SIZE)
        throw std::logic_error(
                "Count is too big. Expected at most" + std::to_string(WriteReply::MAX_DATA_SIZE) + ", but got " +
                std::to_string(this->count));
}

int16_t WriteReply::getCount() const
{
    return this->count;
}

const MyNFSError &WriteReply::getError() const
{
    return this->error;
}

DomainData WriteReply::serialize() const
{
    // convert count
    std::vector<std::byte> dataBytes = Converter::getBytesFromInt16(this->count);

    return DomainData(dataBytes);
}

bool WriteReply::operator==(const WriteReply &rhs) const
{
    return count == rhs.count &&
           error == rhs.error;
}

bool WriteReply::operator!=(const WriteReply &rhs) const
{
    return !(rhs == *this);
}

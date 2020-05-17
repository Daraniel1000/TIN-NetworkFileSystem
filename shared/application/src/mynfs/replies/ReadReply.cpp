#include <session/Converter.h>
#include "application/mynfs/replies/ReadReply.h"

const int16_t ReadReply::MAX_DATA_SIZE = 4096;

ReadReply::ReadReply(void const *buf, int16_t count, ReadReplyError error) : readData(buf, count),
                                                                             error(std::move(error))
{
    if (this->readData.getSize() > ReadReply::MAX_DATA_SIZE)
        throw std::logic_error(
                "Data size is too big. Expected at most" + std::to_string(ReadReply::MAX_DATA_SIZE) + ", but got " +
                std::to_string(this->readData.getSize()));
}

ReadReply::ReadReply(const DomainData &data, PlainError error) : readData(data.getData()), error(std::move(error))
{
    auto expectedSize = sizeof(ReadReply::MAX_DATA_SIZE);
    if (data.getSize() < expectedSize)
        throw std::logic_error(
                "Bad message size. Expected at least" + std::to_string(expectedSize) + ", but got " +
                std::to_string(data.getSize()));

    expectedSize += ReadReply::MAX_DATA_SIZE;
    if (data.getSize() > expectedSize)
        throw std::logic_error(
                "Bad message size. Expected at most" + std::to_string(expectedSize) + ", but got " +
                std::to_string(data.getSize()));

    auto dataOffset = 0;

    //get data size
    auto dataSize = Converter::getInt16FromBytes(
            data.getNBytes(sizeof(ReadReply::MAX_DATA_SIZE), dataOffset));
    dataOffset += sizeof(dataSize);

    //get data
    auto pathBytes = data.getNBytes(dataSize, dataOffset);
    this->readData = PlainData(pathBytes);
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
    // convert data size
    std::vector<std::byte> dataBytes = Converter::getBytesFromInt16(this->readData.getSize());

    // convert data
    auto readDataBytes = this->readData.getData();
    dataBytes.insert(dataBytes.end(), readDataBytes.begin(), readDataBytes.end());

    return DomainData(dataBytes);
}

bool ReadReply::operator==(const ReadReply &rhs) const
{
    return readData == rhs.readData &&
           error == rhs.error;
}

bool ReadReply::operator!=(const ReadReply &rhs) const
{
    return !(rhs == *this);
}

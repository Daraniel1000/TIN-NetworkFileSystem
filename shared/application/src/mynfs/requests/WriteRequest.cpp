#include <stdexcept>
#include <session/Converter.h>
#include "application/mynfs/requests/WriteRequest.h"

const uint8_t WriteRequest::TYPE = 2;
const int16_t WriteRequest::MAX_DATA_SIZE = 4096;

WriteRequest::WriteRequest(int16_t descriptor, void const *buf, int16_t count) : descriptor(descriptor), writeData(buf, count)
{
    if (this->writeData.getSize() > WriteRequest::MAX_DATA_SIZE)
        throw std::logic_error(
                "Data is too big. Expected at most" + std::to_string(WriteRequest::MAX_DATA_SIZE) + ", but got " +
                std::to_string(this->writeData.getSize()));
}

WriteRequest::WriteRequest(const DomainData &data)
{
    auto expectedSize = sizeof(this->descriptor) + sizeof(WriteRequest::MAX_DATA_SIZE);
    if (data.getSize() < expectedSize)
        throw std::logic_error(
                "Bad message size. Expected at least" + std::to_string(expectedSize) + ", but got " +
                std::to_string(data.getSize()));

    expectedSize += WriteRequest::MAX_DATA_SIZE;
    if (data.getSize() > expectedSize)
        throw std::logic_error(
                "Bad message size. Expected at most" + std::to_string(expectedSize) + ", but got " +
                std::to_string(data.getSize()));

    auto dataOffset = 0;
    //get descriptor
    this->descriptor = Converter::getInt16FromBytes(
            data.getNBytes(sizeof(this->descriptor), dataOffset));
    dataOffset += sizeof(this->descriptor);

    //get data size
    auto dataSize = Converter::getInt16FromBytes(
            data.getNBytes(sizeof(WriteRequest::MAX_DATA_SIZE), dataOffset));
    dataOffset += sizeof(dataSize);

    //get data
    auto pathBytes = data.getNBytes(dataSize, dataOffset);
    this->writeData = PlainData(pathBytes);
}

int16_t WriteRequest::getDescriptor() const
{
    return this->descriptor;
}

const PlainData &WriteRequest::getWriteData() const
{
    return this->writeData;
}

uint8_t WriteRequest::getType() const
{
    return WriteRequest::TYPE;
}

DomainData WriteRequest::serialize() const
{
    // convert descriptor
    std::vector<std::byte> dataBytes = Converter::getBytesFromInt16(this->descriptor);

    // convert data size
    auto dataSizeBytes = Converter::getBytesFromInt16(this->writeData.getSize());
    dataBytes.insert(dataBytes.end(), dataSizeBytes.begin(), dataSizeBytes.end());

    // convert data
    auto writeDataBytes = this->writeData.getData();
    dataBytes.insert(dataBytes.end(), writeDataBytes.begin(), writeDataBytes.end());

    return DomainData(dataBytes);
}

bool WriteRequest::operator==(const WriteRequest &rhs) const
{
    return descriptor == rhs.descriptor &&
           writeData == rhs.writeData;
}

bool WriteRequest::operator!=(const WriteRequest &rhs) const
{
    return !(rhs == *this);
}

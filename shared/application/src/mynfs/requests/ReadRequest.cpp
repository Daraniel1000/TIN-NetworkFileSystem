#include <stdexcept>
#include <session/Converter.h>
#include <application/mynfs/bad_argument_error.h>
#include "application/mynfs/requests/ReadRequest.h"

const uint8_t ReadRequest::TYPE = 1;
const int16_t ReadRequest::MAX_DATA_SIZE = 4096;

ReadRequest::ReadRequest(int16_t descriptor, int16_t count) : descriptor(descriptor), count(count)
{
    if (this->count > ReadRequest::MAX_DATA_SIZE)
        throw bad_argument_error(1, 2,
                "Count is too big. Expected at most" + std::to_string(ReadRequest::MAX_DATA_SIZE) + ", but got " +
                std::to_string(this->count));
}

ReadRequest::ReadRequest(const DomainData &data)
{
    auto expectedSize = sizeof(this->descriptor) + sizeof(this->count);
    if (data.getSize() != expectedSize)
        throw bad_argument_error(1, 1,
                "Bad message size. Expected " + std::to_string(expectedSize) + ", but got " +
                std::to_string(data.getSize()));

    auto dataOffset = 0;
    //get descriptor
    this->descriptor = Converter::getInt16FromBytes(
            data.getNBytes(sizeof(this->descriptor), dataOffset));
    dataOffset += sizeof(this->descriptor);

    //get count
    this->count = Converter::getInt16FromBytes(
            data.getNBytes(sizeof(this->count), dataOffset));

    if (this->count > ReadRequest::MAX_DATA_SIZE)
        throw bad_argument_error(1, 2,
                "Count is too big. Expected at most" + std::to_string(ReadRequest::MAX_DATA_SIZE) + ", but got " +
                std::to_string(this->count));
}

int16_t ReadRequest::getDescriptor() const
{
    return this->descriptor;
}

int16_t ReadRequest::getCount() const
{
    return this->count;
}

uint8_t ReadRequest::getType() const
{
    return ReadRequest::TYPE;
}

DomainData ReadRequest::serialize() const
{
    // convert descriptor
    std::vector<std::byte> dataBytes = Converter::getBytesFromUint16(this->descriptor);

    // convert count
    auto countBytes = Converter::getBytesFromInt16(this->count);
    dataBytes.insert(dataBytes.end(), countBytes.begin(), countBytes.end());

    return DomainData(dataBytes);
}

bool ReadRequest::operator==(const ReadRequest &rhs) const
{
    return descriptor == rhs.descriptor &&
           count == rhs.count;
}

bool ReadRequest::operator!=(const ReadRequest &rhs) const
{
    return !(rhs == *this);
}

#include <stdexcept>
#include <session/Converter.h>
#include <algorithm>
#include <sstream>
#include <application/mynfs/bad_argument_error.h>
#include "application/mynfs/requests/LseekRequest.h"

const uint8_t LseekRequest::TYPE = 3;

void checkWhence(int8_t value)
{
    std::vector<int8_t> possibleValues{SEEK_SET, SEEK_CUR, SEEK_END};

    if (std::find(possibleValues.begin(), possibleValues.end(), value) == possibleValues.end())
    {
        std::stringstream ss;
        for (size_t i = 0; i < possibleValues.size(); ++i)
        {
            if (i != 0)
                ss << ",";
            ss << possibleValues[i];
        }
        std::string s = ss.str();

        throw bad_argument_error(1, 2,
                "Invalid whence value " + std::to_string(value) + ". Only possible values are: " + s);
    }
}


LseekRequest::LseekRequest(int16_t descriptor, int32_t offset, int8_t whence) : descriptor(descriptor), offset(offset), whence(whence)
{
    checkWhence(whence);
}

LseekRequest::LseekRequest(const DomainData &data)
{
    auto expectedSize = sizeof(this->descriptor) + sizeof(this->offset) + sizeof(this->whence);
    if (data.getSize() != expectedSize)
        throw bad_argument_error(1, 1,
                "Bad message size. Expected " + std::to_string(expectedSize) + ", but got " +
                std::to_string(data.getSize()));

    auto dataOffset = 0;
    //get descriptor
    this->descriptor = Converter::getInt16FromBytes(
            data.getNBytes(sizeof(this->descriptor), dataOffset));
    dataOffset += sizeof(this->descriptor);

    //get offset
    this->offset = Converter::getInt32FromBytes(
            data.getNBytes(sizeof(this->offset), dataOffset));
    dataOffset += sizeof(this->offset);

    //get whence
    this->whence = Converter::getInt8FromBytes(
            data.getNBytes(sizeof(this->whence), dataOffset));

    checkWhence(this->whence);
}

int16_t LseekRequest::getDescriptor() const
{
    return this->descriptor;
}

int32_t LseekRequest::getOffset() const
{
    return this->offset;
}

int8_t LseekRequest::getWhence() const
{
    return this->whence;
}

uint8_t LseekRequest::getType() const
{
    return LseekRequest::TYPE;
}

DomainData LseekRequest::serialize() const
{
    // convert descriptor
    std::vector<std::byte> dataBytes = Converter::getBytesFromUint16(this->descriptor);

    // convert offset
    auto offsetBytes = Converter::getBytesFromInt32(this->offset);
    dataBytes.insert(dataBytes.end(), offsetBytes.begin(), offsetBytes.end());

    // convert whence
    auto whenceBytes = Converter::getBytesFromInt8(this->whence);
    dataBytes.insert(dataBytes.end(), whenceBytes.begin(), whenceBytes.end());

    return DomainData(dataBytes);
}

bool LseekRequest::operator==(const LseekRequest &rhs) const
{
    return descriptor == rhs.descriptor &&
           offset == rhs.offset &&
           whence == rhs.whence;
}

bool LseekRequest::operator!=(const LseekRequest &rhs) const
{
    return !(rhs == *this);
}

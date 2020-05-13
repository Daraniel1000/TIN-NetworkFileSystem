#include "transport/PlainData.h"

PlainData::PlainData(void *byteArray, unsigned int length)
{
    this->append(byteArray, length);
}

void PlainData::append(void *byteArray, unsigned int length)
{
    auto charByteArray = static_cast<std::byte*>(byteArray);
    this->byteVector.insert(this->byteVector.end(), charByteArray, charByteArray + length);
}

const std::vector<std::byte> &PlainData::getData() const
{
    return this->byteVector;
}

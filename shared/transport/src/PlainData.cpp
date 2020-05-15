#include "transport/PlainData.h"

#include <utility>
#include <stdexcept>

PlainData::PlainData(void *byteArray, unsigned int length)
{
    this->append(byteArray, length);
}

PlainData::PlainData(std::vector<std::byte> byteVector) : byteVector(std::move(byteVector)) {}

void PlainData::append(void *byteArray, unsigned int length)
{
    auto charByteArray = static_cast<std::byte *>(byteArray);
    this->byteVector.insert(this->byteVector.end(), charByteArray, charByteArray + length);
}

const std::vector<std::byte> &PlainData::getData() const
{
    return this->byteVector;
}

size_t PlainData::getSize() const
{
    return this->byteVector.size();
}

std::vector<std::byte> PlainData::getNBytes(size_t n, size_t offset) const
{
    if(offset + n > this->getSize())
        throw std::out_of_range("Number of bytes is out of range for this data");
    return std::vector<std::byte>(this->byteVector.begin() + offset, this->byteVector.begin() + offset + n);
}
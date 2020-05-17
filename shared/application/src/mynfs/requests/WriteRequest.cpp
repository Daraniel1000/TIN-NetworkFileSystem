#include "application/mynfs/requests/WriteRequest.h"

const uint8_t WriteRequest::TYPE = 2;

WriteRequest::WriteRequest(int16_t descriptor, void const *buf, int16_t count)
{

}

WriteRequest::WriteRequest(const DomainData &data)
{

}

int16_t WriteRequest::getDescriptor() const
{
    return 0;
}

const PlainData &WriteRequest::getWriteData() const
{
    return this->writeData;
}

uint8_t WriteRequest::getType() const
{
    return 0;
}

DomainData WriteRequest::serialize() const
{
    return DomainData();
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

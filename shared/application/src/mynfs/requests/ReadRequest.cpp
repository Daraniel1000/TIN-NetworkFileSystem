#include "application/mynfs/requests/ReadRequest.h"

const uint8_t ReadRequest::TYPE = 1;

ReadRequest::ReadRequest(int16_t descriptor, int16_t count)
{

}

ReadRequest::ReadRequest(const DomainData &data)
{

}

int16_t ReadRequest::getDescriptor() const
{
    return 0;
}

int16_t ReadRequest::getCount() const
{
    return 0;
}

uint8_t ReadRequest::getType() const
{
    return 0;
}

DomainData ReadRequest::serialize() const
{
    return DomainData();
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

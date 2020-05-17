#include "application/mynfs/requests/CloseRequest.h"

const uint8_t CloseRequest::TYPE = 4;

CloseRequest::CloseRequest(int16_t descriptor)
{

}

CloseRequest::CloseRequest(const DomainData &data)
{

}

int16_t CloseRequest::getDescriptor() const
{
    return 0;
}

uint8_t CloseRequest::getType() const
{
    return 0;
}

DomainData CloseRequest::serialize() const
{
    return DomainData();
}

bool CloseRequest::operator==(const CloseRequest &rhs) const
{
    return descriptor == rhs.descriptor;
}

bool CloseRequest::operator!=(const CloseRequest &rhs) const
{
    return !(rhs == *this);
}

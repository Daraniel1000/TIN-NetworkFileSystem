#include "application/mynfs/requests/LseekRequest.h"

const uint8_t LseekRequest::TYPE = 3;

LseekRequest::LseekRequest(int16_t descriptor, int32_t offset, int8_t whence)
{

}

LseekRequest::LseekRequest(const DomainData &data)
{

}

int16_t LseekRequest::getDescriptor() const
{
    return 0;
}

int32_t LseekRequest::getOffset() const
{
    return 0;
}

int8_t LseekRequest::getWhence() const
{
    return 0;
}

uint8_t LseekRequest::getType() const
{
    return 0;
}

DomainData LseekRequest::serialize() const
{
    return DomainData();
}

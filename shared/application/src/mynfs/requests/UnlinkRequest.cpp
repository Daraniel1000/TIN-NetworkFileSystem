#include "application/mynfs/requests/UnlinkRequest.h"

const uint8_t UnlinkRequest::TYPE = 5;
const int16_t UnlinkRequest::MAX_PATH_SIZE = 4096;

UnlinkRequest::UnlinkRequest(char const *path)
{

}

UnlinkRequest::UnlinkRequest(const DomainData &data)
{

}

const std::string &UnlinkRequest::getPath() const
{
    return this->path;
}

uint8_t UnlinkRequest::getType() const
{
    return 0;
}

DomainData UnlinkRequest::serialize() const
{
    return DomainData();
}

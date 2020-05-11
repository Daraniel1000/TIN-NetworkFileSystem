#include "application/mynfs/requests/OpenRequest.h"

OpenRequest::OpenRequest(char *path, uint8_t oflag)
{

}

OpenRequest::OpenRequest(DomainData data)
{

}

const std::string &OpenRequest::getPath()
{
    return this->path;
}

uint8_t OpenRequest::getOflag()
{
    return this->oflag;
}


int8_t OpenRequest::getType() const
{
    return 0;
}

DomainData OpenRequest::getData() const
{
    return DomainData();
}
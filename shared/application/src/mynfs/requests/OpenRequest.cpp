#include "application/mynfs/requests/OpenRequest.h"

OpenRequest::OpenRequest(char *path, uint8_t oflag)
{

}


int8_t OpenRequest::getType() const
{
    return 0;
}

DomainData OpenRequest::getData() const
{
    return DomainData();
}
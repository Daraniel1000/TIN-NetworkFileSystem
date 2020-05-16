#include <session/Converter.h>
#include <stdexcept>
#include <fcntl.h>
#include <algorithm>
#include <sstream>
#include <application/mynfs/requests/ReadRequest.h>

#include "application/mynfs/requests/ReadRequest.h"

ReadRequest::ReadRequest(int16_t fd, void *buf, int16_t count) : fd(fd), buf(buf), count(count)
{
    if (this->count <= 0)
        throw std::logic_error("Count bytes to read up must be a positive number.");
}

ReadRequest::ReadRequest(const DomainData &data)
{

}

uint8_t ReadRequest::getType() const
{
    return 3;
}

DomainData ReadRequest::getData() const
{
    return DomainData({});
}

int16_t ReadRequest::getFileDescriptor()
{
    return this->fd;
};
int16_t ReadRequest::getCount()
{
    return this->count;
}

void * ReadRequest::getBuf() const
{
    return this->buf;
};
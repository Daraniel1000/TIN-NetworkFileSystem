#ifndef MYNFS_REQUEST_H
#define MYNFS_REQUEST_H

#include <session/DomainData.h>

class Request
{
public:
    virtual ~Request() = default;

    virtual int8_t getType() const = 0;
    virtual DomainData getData() const = 0;
};


#endif //MYNFS_REQUEST_H

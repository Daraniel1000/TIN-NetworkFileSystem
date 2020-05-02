#ifndef MYNFS_OPENREQUEST_H
#define MYNFS_OPENREQUEST_H


#include <cstdint>
#include "Request.h"

class OpenRequest : public Request
{
public:
    OpenRequest(char *path, uint8_t oflag);

    int8_t getType() const override;
    DomainData getData() const override;
};


#endif //MYNFS_OPENREQUEST_H

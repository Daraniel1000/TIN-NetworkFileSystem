#ifndef MYNFS_OPENREQUEST_H
#define MYNFS_OPENREQUEST_H


#include <cstdint>
#include <string>
#include "Request.h"

class OpenRequest : public Request
{
    std::string path;
    uint8_t oflag;
public:
    OpenRequest(char *path, uint8_t oflag);
    OpenRequest(DomainData data);

    const std::string& getPath();
    uint8_t getOflag();

    int8_t getType() const override;
    DomainData getData() const override;
};


#endif //MYNFS_OPENREQUEST_H

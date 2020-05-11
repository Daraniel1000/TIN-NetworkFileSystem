#ifndef MYNFS_REPLY_H
#define MYNFS_REPLY_H

#include <cstdint>
#include <session/DomainData.h>

class Reply
{
    int8_t error;
public:
    Reply(int8_t error) : error(error) {}
    virtual ~Reply() = default;

    virtual int8_t getError() = 0;
    virtual DomainData getData() const = 0;
};


#endif //MYNFS_REPLY_H

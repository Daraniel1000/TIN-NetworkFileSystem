#ifndef MYNFS_REPLY_H
#define MYNFS_REPLY_H

#include <cstdint>

class Reply
{
public:
    virtual ~Reply() = default;

    virtual int8_t getError() = 0;
};


#endif //MYNFS_REPLY_H

#ifndef MYNFS_MESSAGE_H
#define MYNFS_MESSAGE_H

#include "PlainData.h"

class Message
{
public:
    virtual ~Message() = default;

    virtual PlainData serialize() = 0;
};


#endif //MYNFS_MESSAGE_H

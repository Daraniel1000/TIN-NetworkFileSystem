#ifndef MYNFS_MESSAGE_H
#define MYNFS_MESSAGE_H

#include <transport/PlainData.h>

class Message
{
public:
    virtual ~Message() = default;

    /**
     * Transform message object to plain bytes
     */
    virtual PlainData serialize() = 0;
};


#endif //MYNFS_MESSAGE_H

#ifndef MYNFS_REQUESTMESSAGE_H
#define MYNFS_REQUESTMESSAGE_H

#include <cstdint>
#include "Message.h"

class RequestMessage : public Message
{
    int8_t type;
public:
    RequestMessage(int8_t type);
    RequestMessage(PlainData data);

    int8_t getType() const;

    PlainData serialize() override;
};


#endif //MYNFS_REQUESTMESSAGE_H

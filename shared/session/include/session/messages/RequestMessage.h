#ifndef MYNFS_REQUESTMESSAGE_H
#define MYNFS_REQUESTMESSAGE_H

#include <cstdint>
#include "Message.h"

class RequestMessage : public Message
{
public:
    RequestMessage() = default;
    RequestMessage(PlainData data);

    PlainData serialize() override;
};


#endif //MYNFS_REQUESTMESSAGE_H

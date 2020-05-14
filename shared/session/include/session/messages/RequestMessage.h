#ifndef MYNFS_REQUESTMESSAGE_H
#define MYNFS_REQUESTMESSAGE_H

#include <cstdint>
#include "Message.h"

class RequestMessage : public Message
{
public:
    /**
     * Create message (sending side)
     */
    RequestMessage() = default;

    /**
     * Deserialize message (receiving side)
     */
    explicit RequestMessage(PlainData data);

    PlainData serialize() override;
};


#endif //MYNFS_REQUESTMESSAGE_H

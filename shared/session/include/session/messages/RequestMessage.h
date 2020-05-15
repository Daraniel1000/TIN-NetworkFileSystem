#ifndef MYNFS_REQUESTMESSAGE_H
#define MYNFS_REQUESTMESSAGE_H

#include <cstdint>
#include "Message.h"

class RequestMessage : public Message
{
    static const uint8_t MESSAGE_TYPE = 0;
public:
    /**
     * Create message (sending side)
     */
    RequestMessage() = default;

    /**
     * Deserialize message (receiving side)
     */
    explicit RequestMessage(const PlainData& data);

    PlainData serialize() const override;
};


#endif //MYNFS_REQUESTMESSAGE_H

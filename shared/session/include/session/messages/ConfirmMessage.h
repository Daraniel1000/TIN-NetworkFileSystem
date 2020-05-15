#ifndef MYNFS_CONFIRMMESSAGE_H
#define MYNFS_CONFIRMMESSAGE_H

#include <cstdint>
#include "Message.h"
#include "session/PlainError.h"

class ConfirmMessage : public Message
{
    static const uint8_t MESSAGE_TYPE = 1;

    PlainError error;
public:
    /**
     * Create message from arguments (sending side)
     * @param error if some error happened while handling request, pass it here
     */
    explicit ConfirmMessage(const PlainError& error = PlainError(0));

    /**
     * Deserialize message (receiving side)
     */
    explicit ConfirmMessage(const PlainData& data);

    const PlainError& getError() const;

    PlainData serialize() const override;
};


#endif //MYNFS_CONFIRMMESSAGE_H

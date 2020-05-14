#ifndef MYNFS_CONFIRMMESSAGE_H
#define MYNFS_CONFIRMMESSAGE_H

#include <cstdint>
#include "Message.h"
#include "session/PlainError.h"

class ConfirmMessage : public Message
{
    PlainError error;
public:
    /**
     * Create message from arguments (sending side)
     * @param error if some error happened while handling request, pass it here
     */
    explicit ConfirmMessage(PlainError error = PlainError(0));

    /**
     * Deserialize message (receiving side)
     */
    explicit ConfirmMessage(PlainData data);

    PlainData serialize() override;
};


#endif //MYNFS_CONFIRMMESSAGE_H

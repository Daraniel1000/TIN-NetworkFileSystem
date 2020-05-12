#ifndef MYNFS_CONFIRMMESSAGE_H
#define MYNFS_CONFIRMMESSAGE_H

#include <cstdint>
#include "Message.h"

class ConfirmMessage : public Message
{
    int8_t error;
public:
    /**
     * Create message from arguments (sending side)
     * @param error if some error happened while handling request, pass it here
     */
    ConfirmMessage(int8_t error = 0);

    /**
     * Deserialize message (receiving side)
     */
    ConfirmMessage(PlainData data);

    PlainData serialize() override;
};


#endif //MYNFS_CONFIRMMESSAGE_H

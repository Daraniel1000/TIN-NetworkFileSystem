#ifndef MYNFS_CONFIRMMESSAGE_H
#define MYNFS_CONFIRMMESSAGE_H

#include <cstdint>
#include "Message.h"

class ConfirmMessage : public Message
{
    int8_t error;
public:
    ConfirmMessage(int8_t error = 0);
    ConfirmMessage(PlainData data);

    PlainData serialize() override;
};


#endif //MYNFS_CONFIRMMESSAGE_H

#ifndef MYNFS_CONFIRMMESSAGE_H
#define MYNFS_CONFIRMMESSAGE_H

#include "Message.h"

class ConfirmMessage : public Message
{
public:
    ConfirmMessage();
    ConfirmMessage(PlainData data);

    PlainData serialize() override;
};


#endif //MYNFS_CONFIRMMESSAGE_H

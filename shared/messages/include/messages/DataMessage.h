#ifndef MYNFS_DATAMESSAGE_H
#define MYNFS_DATAMESSAGE_H

#include "Message.h"
#include "DomainData.h"

class DataMessage : public Message
{
public:
    DataMessage(DomainData data);
    DataMessage(PlainData data);

    PlainData serialize() override;
};


#endif //MYNFS_DATAMESSAGE_H
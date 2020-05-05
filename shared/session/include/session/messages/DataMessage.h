#ifndef MYNFS_DATAMESSAGE_H
#define MYNFS_DATAMESSAGE_H

#include "Message.h"
#include "session/DomainData.h"

class DataMessage : public Message
{
    DomainData data;
public:
    DataMessage(DomainData data);
    DataMessage(PlainData data);

    DomainData getData();

    PlainData serialize() override;
};


#endif //MYNFS_DATAMESSAGE_H
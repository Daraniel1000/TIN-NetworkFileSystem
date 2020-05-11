#ifndef MYNFS_DATAMESSAGE_H
#define MYNFS_DATAMESSAGE_H

#include <cstdint>
#include "Message.h"
#include "session/DomainData.h"

class DataMessage : public Message
{
    int8_t type;
    DomainData data;
public:
    DataMessage(int8_t type, DomainData data);
    DataMessage(PlainData data);

    int8_t getType();
    DomainData getData();

    PlainData serialize() override;
};


#endif //MYNFS_DATAMESSAGE_H
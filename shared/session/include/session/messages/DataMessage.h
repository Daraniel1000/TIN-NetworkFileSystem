#ifndef MYNFS_DATAMESSAGE_H
#define MYNFS_DATAMESSAGE_H

#include <cstdint>
#include "Message.h"
#include "session/DomainData.h"

class DataMessage : public Message
{
    int8_t type;
    int8_t error;
    DomainData data;
public:
    DataMessage(int8_t type, DomainData data, int8_t error = 0);
    DataMessage(PlainData data);

    int8_t getType();
    int8_t getError();
    DomainData getData();

    PlainData serialize() override;
};


#endif //MYNFS_DATAMESSAGE_H
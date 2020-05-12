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
    /**
     * Create message from arguments (sending side)
     * @param type type of request this message is bound to
     * @param data message plain data
     * @param error if some error happened while handling request, pass it here
     *
     * If error is nonzero other arguments can be anything as they should be ignored by receiving side
     */
    DataMessage(int8_t type, DomainData data, int8_t error = 0);

    /**
     * Deserialize message (receiving side)
     */
    DataMessage(PlainData data);

    /**
     * Get type of request this message is bound to
     */
    int8_t getType();

    /**
     * Get message error
     * If there is some error on server side, it will be available for the client here
     */
    int8_t getError();

    /**
     * Get message plain domain data (not serialization, only data getter)
     */
    DomainData getData();

    PlainData serialize() override;
};


#endif //MYNFS_DATAMESSAGE_H
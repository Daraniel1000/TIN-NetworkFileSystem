#ifndef MYNFS_DATAMESSAGE_H
#define MYNFS_DATAMESSAGE_H

#include <cstdint>
#include "Message.h"
#include "session/DomainData.h"
#include "session/PlainError.h"

class DataMessage : public Message
{
    int8_t type;
    PlainError error;
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
    DataMessage(int8_t type, DomainData data, PlainError error = PlainError());

    /**
     * Deserialize message (receiving side)
     */
    explicit DataMessage(PlainData data);

    /**
     * Get type of request this message is bound to
     */
    int8_t getType();

    /**
     * Get message error
     * If there is some error on server side, it will be available for the client here
     */
    PlainError getError();

    /**
     * Get message plain domain data (not serialization, only data getter)
     */
    DomainData getData();

    PlainData serialize() override;
};


#endif //MYNFS_DATAMESSAGE_H
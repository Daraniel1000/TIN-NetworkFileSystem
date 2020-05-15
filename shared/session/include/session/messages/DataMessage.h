#ifndef MYNFS_DATAMESSAGE_H
#define MYNFS_DATAMESSAGE_H

#include <cstdint>
#include "Message.h"
#include "session/DomainData.h"
#include "session/PlainError.h"

class DataMessage : public Message
{
    static const uint8_t MESSAGE_TYPE = 2;

    PlainError error;
    int8_t type;
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
    explicit DataMessage(const PlainData& data);

    /**
     * Get message error
     * If there is some error on server side, it will be available for the client here
     */
    const PlainError& getError() const;

    /**
     * Get type of request this message is bound to
     */
    int8_t getType() const;

    /**
     * Get message plain domain data (not serialization, only data getter)
     */
    const DomainData& getData() const;

    PlainData serialize() const override;
};


#endif //MYNFS_DATAMESSAGE_H
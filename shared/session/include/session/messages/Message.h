#ifndef MYNFS_MESSAGE_H
#define MYNFS_MESSAGE_H

#include <transport/PlainData.h>
#include <cstdint>

class Message
{

protected:
    static void checkDataType(const PlainData& data, uint8_t expectedType);
    static void checkDataSize(const PlainData& data, size_t expectedSize);

public:
    virtual ~Message() = default;

    /**
     * Transform message object to plain bytes
     */
    virtual PlainData serialize() const = 0;
};

#endif //MYNFS_MESSAGE_H

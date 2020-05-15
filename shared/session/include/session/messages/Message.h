#ifndef MYNFS_MESSAGE_H
#define MYNFS_MESSAGE_H

#include <transport/PlainData.h>
#include <cstring>
#include <cstdint>
#include <netinet/in.h>

class Message
{

protected:
    static void checkDataType(const PlainData& data, uint8_t expectedType);
    static void checkDataSize(const PlainData& data, size_t expectedSize);

    static uint8_t getUint8FromBytes(const std::vector<std::byte>& bytes);
    static uint16_t getUint16FromBytes(const std::vector<std::byte>& bytes);
    static uint32_t getUint32FromBytes(const std::vector<std::byte>& bytes);

    static std::vector<std::byte> getBytesFromUint8(uint8_t value);
    static std::vector<std::byte> getBytesFromUint16(uint16_t value);
    static std::vector<std::byte> getBytesFromUint32(uint32_t value);

public:
    virtual ~Message() = default;

    /**
     * Transform message object to plain bytes
     */
    virtual PlainData serialize() const = 0;
};

#endif //MYNFS_MESSAGE_H

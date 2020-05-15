#include <stdexcept>
#include "session/messages/Message.h"


void Message::checkDataSize(const PlainData &data, size_t expectedSize)
{
    if (data.getSize() != expectedSize)
        throw std::logic_error(
                "Bad message size. Expected " + std::to_string(expectedSize) + ", but got " +
                std::to_string(data.getSize()));
}

void Message::checkDataType(const PlainData& data, uint8_t expectedType)
{
    auto msgType = Message::getUint8FromBytes(data.getNBytes(sizeof(uint8_t), 0));
    if (msgType != expectedType)
        throw std::logic_error(
                "Bad message type. Expected: " + std::to_string(expectedType) + ", but got " +
                std::to_string(msgType));
}


uint8_t Message::getUint8FromBytes(const std::vector<std::byte> &bytes)
{
    uint8_t value;
    memcpy(&value, bytes.data(), bytes.size());
    return value;
}

uint16_t Message::getUint16FromBytes(const std::vector<std::byte> &bytes)
{
    uint16_t value;
    memcpy(&value, bytes.data(), bytes.size());
    return ntohs(value);
}

uint32_t Message::getUint32FromBytes(const std::vector<std::byte> &bytes)
{
    uint32_t value;
    memcpy(&value, bytes.data(), bytes.size());
    return ntohl(value);
}

std::vector<std::byte> Message::getBytesFromUint8(uint8_t value)
{
    auto byteValuePtr = static_cast<std::byte*>(static_cast<void*>(&value));
    return std::vector<std::byte>(byteValuePtr, byteValuePtr + sizeof(value));
}

std::vector<std::byte> Message::getBytesFromUint16(uint16_t value)
{
    value = htons(value);
    auto byteValuePtr = static_cast<std::byte*>(static_cast<void*>(&value));
    return std::vector<std::byte>(byteValuePtr, byteValuePtr + sizeof(value));
}

std::vector<std::byte> Message::getBytesFromUint32(uint32_t value)
{
    value = htonl(value);
    auto byteValuePtr = static_cast<std::byte*>(static_cast<void*>(&value));
    return std::vector<std::byte>(byteValuePtr, byteValuePtr + sizeof(value));
}
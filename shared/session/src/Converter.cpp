#include <cstring>
#include <netinet/in.h>
#include "session/Converter.h"

uint8_t Converter::getUint8FromBytes(const std::vector<std::byte> &bytes)
{
    uint8_t value;
    memcpy(&value, bytes.data(), bytes.size());
    return value;
}

uint16_t Converter::getUint16FromBytes(const std::vector<std::byte> &bytes)
{
    uint16_t value;
    memcpy(&value, bytes.data(), bytes.size());
    return ntohs(value);
}

uint32_t Converter::getUint32FromBytes(const std::vector<std::byte> &bytes)
{
    uint32_t value;
    memcpy(&value, bytes.data(), bytes.size());
    return ntohl(value);
}

std::vector<std::byte> Converter::getBytesFromUint8(uint8_t value)
{
    auto byteValuePtr = static_cast<std::byte*>(static_cast<void*>(&value));
    return std::vector<std::byte>(byteValuePtr, byteValuePtr + sizeof(value));
}

std::vector<std::byte> Converter::getBytesFromUint16(uint16_t value)
{
    value = htons(value);
    auto byteValuePtr = static_cast<std::byte*>(static_cast<void*>(&value));
    return std::vector<std::byte>(byteValuePtr, byteValuePtr + sizeof(value));
}

std::vector<std::byte> Converter::getBytesFromUint32(uint32_t value)
{
    value = htonl(value);
    auto byteValuePtr = static_cast<std::byte*>(static_cast<void*>(&value));
    return std::vector<std::byte>(byteValuePtr, byteValuePtr + sizeof(value));
}

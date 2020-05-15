#ifndef MYNFS_CONVERTER_H
#define MYNFS_CONVERTER_H


#include <vector>
#include <cstdint>

class Converter
{
public:
    static uint8_t getUint8FromBytes(const std::vector<std::byte>& bytes);
    static uint16_t getUint16FromBytes(const std::vector<std::byte>& bytes);
    static uint32_t getUint32FromBytes(const std::vector<std::byte>& bytes);

    static std::vector<std::byte> getBytesFromUint8(uint8_t value);
    static std::vector<std::byte> getBytesFromUint16(uint16_t value);
    static std::vector<std::byte> getBytesFromUint32(uint32_t value);
};


#endif //MYNFS_CONVERTER_H

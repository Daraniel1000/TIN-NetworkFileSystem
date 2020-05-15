#ifndef MYNFS_CONVERTER_H
#define MYNFS_CONVERTER_H


#include <vector>
#include <cstdint>

class Converter
{
public:
    /**
     * Convert from network order bytes to host order uint8_t
     */
    static uint8_t getUint8FromBytes(const std::vector<std::byte>& bytes);
    /**
     * Convert from network order bytes to host order uint16_t
     */
    static uint16_t getUint16FromBytes(const std::vector<std::byte>& bytes);
    /**
     * Convert from network order bytes to host order uint32_t
     */
    static uint32_t getUint32FromBytes(const std::vector<std::byte>& bytes);

    /**
     * Convert from host order uint16_t to network order bytes
     */
    static std::vector<std::byte> getBytesFromUint8(uint8_t value);
    /**
     * Convert from host order uint16_t to network order bytes
     */
    static std::vector<std::byte> getBytesFromUint16(uint16_t value);
    /**
     * Convert from host order uint16_t to network order bytes
     */
    static std::vector<std::byte> getBytesFromUint32(uint32_t value);
};


#endif //MYNFS_CONVERTER_H

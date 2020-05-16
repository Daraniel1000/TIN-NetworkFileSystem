#ifndef MYNFS_CONVERTER_H
#define MYNFS_CONVERTER_H


#include <vector>
#include <cstdint>
#include <cstddef>

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
     * Convert from network order bytes to host order int8_t
     */
    static int8_t getInt8FromBytes(const std::vector<std::byte>& bytes);
    /**
     * Convert from network order bytes to host order int16_t
     */
    static int16_t getInt16FromBytes(const std::vector<std::byte>& bytes);
    /**
     * Convert from network order bytes to host order int32_t
     */
    static int32_t getInt32FromBytes(const std::vector<std::byte>& bytes);

    /**
     * Convert from host order uint8_t to network order bytes
     */
    static std::vector<std::byte> getBytesFromUint8(uint8_t value);
    /**
     * Convert from host order uint16_t to network order bytes
     */
    static std::vector<std::byte> getBytesFromUint16(uint16_t value);
    /**
     * Convert from host order uint32_t to network order bytes
     */
    static std::vector<std::byte> getBytesFromUint32(uint32_t value);

    /**
     * Convert from host order int8_t to network order bytes
     */
    static std::vector<std::byte> getBytesFromInt8(int8_t value);
    /**
     * Convert from host order int16_t to network order bytes
     */
    static std::vector<std::byte> getBytesFromInt16(int16_t value);
    /**
     * Convert from host order int32_t to network order bytes
     */
    static std::vector<std::byte> getBytesFromInt32(int32_t value);
};


#endif //MYNFS_CONVERTER_H

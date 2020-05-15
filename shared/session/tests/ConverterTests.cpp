#include <catch.hpp>

#include "session/Converter.h"

TEST_CASE("Converter correctly converts from uint8 to bytes", "[Converter]")
{
    uint8_t value = 10;
    auto converted = Converter::getBytesFromUint8(value);

    CHECK(converted == std::vector<std::byte>{std::byte(value)});
}

TEST_CASE("Converter correctly converts from uint16 to bytes", "[Converter]")
{
    uint16_t value = 0x1234;
    auto converted = Converter::getBytesFromUint16(value);

    CHECK(converted == std::vector<std::byte>{std::byte(0x12), std::byte(0x34)});
}

TEST_CASE("Converter correctly converts from uint32 to bytes", "[Converter]")
{
    uint32_t value = 0x12345678;
    auto converted = Converter::getBytesFromUint32(value);

    CHECK(converted == std::vector<std::byte>{std::byte(0x12), std::byte(0x34), std::byte(0x56), std::byte(0x78)});
}

TEST_CASE("Converter correctly converts from bytes to uint8", "[Converter]")
{
    auto bytes = std::vector<std::byte>{std::byte(0x12)};

    auto converted = Converter::getUint8FromBytes(bytes);

    CHECK(converted == 0x12);
}

TEST_CASE("Converter correctly converts from bytes to uint16", "[Converter]")
{
    auto bytes = std::vector<std::byte>{std::byte(0x12), std::byte(0x34)};

    auto converted = Converter::getUint16FromBytes(bytes);

    CHECK(converted == 0x1234);
}

TEST_CASE("Converter correctly converts from bytes to uint32", "[Converter]")
{
    auto bytes = std::vector<std::byte>{std::byte(0x12), std::byte(0x34), std::byte(0x56), std::byte(0x78)};

    auto converted = Converter::getUint32FromBytes(bytes);

    CHECK(converted == 0x12345678);
}
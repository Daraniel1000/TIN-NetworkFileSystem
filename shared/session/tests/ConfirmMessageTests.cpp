#include <catch.hpp>

#include "session/messages/ConfirmMessage.h"

TEST_CASE("ConfirmMessage correctly constructs from empty arguments", "[ConfirmMessage]")
{
    CHECK_NOTHROW(ConfirmMessage());
}

TEST_CASE("ConfirmMessage correctly constructs from arguments", "[ConfirmMessage]")
{
    CHECK_NOTHROW(ConfirmMessage(PlainError(10)));
}

TEST_CASE("ConfirmMessage correctly deserializes", "[ConfirmMessage]")
{
    PlainData data;
    uint8_t msgType = 1;
    data.append(&msgType, sizeof(msgType));
    uint8_t error = 2;
    data.append(&error, sizeof(error));
    CHECK_NOTHROW(ConfirmMessage(data));
    CHECK(ConfirmMessage(data).getError().getErrorValue() == error);
}

TEST_CASE("ConfirmMessage throws when deserialized data size is invalid", "[ConfirmMessage]")
{
    PlainData data({std::byte(0x1), std::byte(0x2), std::byte(0x3), std::byte(0x4)});
    CHECK_THROWS(ConfirmMessage(data));
}

TEST_CASE("ConfirmMessage throws when message type is invalid", "[ConfirmMessage]")
{
    uint8_t msgType = 5;
    PlainData data(&msgType, sizeof(msgType));
    CHECK_THROWS(ConfirmMessage(data));
}

TEST_CASE("ConfirmMessage correctly serializes", "[ConfirmMessage]")
{
    auto serialized = ConfirmMessage(PlainError(2)).serialize();

    PlainData data;
    uint8_t msgType = 1;
    data.append(&msgType, sizeof(msgType));
    uint8_t error = 2;
    data.append(&error, sizeof(error));

    CHECK(serialized == data);
}
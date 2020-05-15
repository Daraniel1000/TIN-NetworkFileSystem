#include <catch.hpp>

#include "session/messages/RequestMessage.h"

TEST_CASE("RequestMessage correctly constructs from arguments", "[RequestMessage]")
{
    CHECK_NOTHROW(RequestMessage());
}

TEST_CASE("RequestMessage correctly deserializes", "[RequestMessage]")
{
    uint8_t msgType = 0;
    PlainData data(&msgType, sizeof(msgType));
    CHECK_NOTHROW(RequestMessage(data));
}

TEST_CASE("RequestMessage throws when deserialized data size is invalid", "[RequestMessage]")
{
    PlainData data({std::byte(0x1), std::byte(0x2), std::byte(0x3)});
    CHECK_THROWS(RequestMessage(data));
}

TEST_CASE("RequestMessage throws when message type is invalid", "[RequestMessage]")
{
    uint8_t msgType = 5;
    PlainData data(&msgType, sizeof(msgType));
    CHECK_THROWS(RequestMessage(data));
}

TEST_CASE("RequestMessage correctly serializes", "[RequestMessage]")
{
    auto serialized = RequestMessage().serialize();

    uint8_t msgType = 0;
    PlainData data(&msgType, sizeof(msgType));

    CHECK(serialized.getData() == data.getData());
}
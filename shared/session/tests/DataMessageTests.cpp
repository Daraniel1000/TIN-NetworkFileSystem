#include <catch.hpp>

#include "session/messages/DataMessage.h"

TEST_CASE("DataMessage correctly constructs from arguments", "[DataMessage]")
{
    auto reqType = 1;
    auto data = DomainData({std::byte(0x1), std::byte(0x2)});
    auto error = PlainError(6);
    CHECK_NOTHROW(DataMessage(reqType, data, error));
}

TEST_CASE("DataMessage correctly deserializes", "[DataMessage]")
{
    PlainData data;
    uint8_t msgType = 2;
    data.append(&msgType, sizeof(msgType));
    uint8_t error = 2;
    data.append(&error, sizeof(error));
    uint8_t reqType = 1;
    data.append(&reqType, sizeof(reqType));
    auto rawData = DomainData({std::byte(0x1), std::byte(0x2)}).getData();
    data.append(rawData.data(), rawData.size());
    CHECK_NOTHROW(DataMessage(data));
    CHECK(DataMessage(data).getType() == reqType);
    CHECK(DataMessage(data).getError().getErrorValue() == error);
    CHECK(DataMessage(data).getData().getData() == rawData);
}

TEST_CASE("DataMessage throws when deserialized data size is invalid", "[DataMessage]")
{
    PlainData data({std::byte(0x1)});
    CHECK_THROWS(DataMessage(data));
}

TEST_CASE("DataMessage throws when message type is invalid", "[DataMessage]")
{
    uint8_t msgType = 5;
    PlainData data(&msgType, sizeof(msgType));
    CHECK_THROWS(DataMessage(data));
}

TEST_CASE("DataMessage correctly serializes", "[DataMessage]")
{
    auto argReqType = 1;
    auto argData = DomainData({std::byte(0x1), std::byte(0x2)});
    auto argError = PlainError(6);

    auto serialized = DataMessage(argReqType, argData, argError).serialize();

    PlainData data;
    uint8_t msgType = 2;
    data.append(&msgType, sizeof(msgType));
    uint8_t error = argError.getErrorValue();
    data.append(&error, sizeof(error));
    uint8_t reqType = argReqType;
    data.append(&reqType, sizeof(reqType));
    auto rawData = argData.getData();
    data.append(rawData.data(), rawData.size());

    CHECK(serialized.getData() == data.getData());
}
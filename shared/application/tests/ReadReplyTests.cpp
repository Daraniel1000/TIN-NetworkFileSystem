#include <catch.hpp>
#include <netinet/in.h>

#include "application/mynfs/replies/ReadReply.h"

TEST_CASE("ReadReply correctly constructs from arguments", "[ReadReply]")
{
    auto data = PlainData({std::byte(0x1), std::byte(0x2)});
    ReadReplyError error(-1);
    CHECK_NOTHROW(ReadReply(data.getData().data(), data.getSize(), error));
    ReadReply rep(data.getData().data(), data.getSize(), error);
    CHECK(rep.getData() == data);
    CHECK(rep.getError().getErrorValue() == error.getErrorValue());
}

TEST_CASE("ReadReply throws with too big data", "[ReadReply]")
{
    auto data = PlainData(std::vector<std::byte>(ReadReply::MAX_DATA_SIZE + 1));
    ReadReplyError error(-1);
    CHECK_THROWS(ReadReply(data.getData().data(), data.getSize(), error));
}

TEST_CASE("ReadReply correctly deserializes", "[ReadReply]")
{
    auto readData = PlainData({std::byte(0x1), std::byte(0x2)});
    DomainData data;
    int16_t dataSize = htons(readData.getSize());
    data.append(&dataSize, sizeof(dataSize));
    data.append(readData.getData().data(), readData.getSize());
    PlainError error(99);

    CHECK_NOTHROW(ReadReply(data, error));
    ReadReply rep(data, error);
    CHECK(rep.getData() == readData);
    CHECK(rep.getError().getErrorValue() == error.getErrorValue());
}

TEST_CASE("ReadReply throws with bad deserialization data size", "[ReadReply]")
{
    auto readData = PlainData({std::byte(0x1), std::byte(0x2)});
    DomainData data;
    int16_t dataSize = htons(readData.getSize());
    data.append(&dataSize, sizeof(dataSize));
    PlainError error(-1);

    CHECK_THROWS(ReadReply(data, error));
}

TEST_CASE("ReadReply throws with too big data when deserializing", "[ReadReply]")
{
    auto readData = PlainData(std::vector<std::byte>(ReadReply::MAX_DATA_SIZE + 1));
    DomainData data;
    int16_t dataSize = htons(readData.getSize());
    data.append(&dataSize, sizeof(dataSize));
    data.append(readData.getData().data(), readData.getSize());
    PlainError error(-1);

    CHECK_THROWS(ReadReply(data, error));
}

TEST_CASE("ReadReply correctly serializes", "[ReadReply]")
{
    auto readData = PlainData({std::byte(0x1), std::byte(0x2)});
    ReadReplyError error(-1);
    auto data = ReadReply(readData.getData().data(), readData.getSize(), error).serialize();

    DomainData expectedData;
    int16_t dataSize = htons(readData.getSize());
    expectedData.append(&dataSize, sizeof(dataSize));
    expectedData.append(readData.getData().data(), readData.getSize());

    CHECK(data == expectedData);
}
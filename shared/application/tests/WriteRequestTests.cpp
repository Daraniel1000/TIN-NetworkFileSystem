#include <catch.hpp>
#include <fcntl.h>
#include <netinet/in.h>

#include "application/mynfs/requests/WriteRequest.h"

TEST_CASE("WriteRequest correctly constructs from arguments", "[WriteRequest]")
{
    int16_t descriptor = 10;
    auto writeData = PlainData({std::byte(0x1), std::byte(0x2)});
    CHECK_NOTHROW(WriteRequest(descriptor, writeData.getData().data(), writeData.getSize()));
    WriteRequest req(descriptor, writeData.getData().data(), writeData.getSize());
    CHECK(req.getDescriptor() == descriptor);
    CHECK(req.getWriteData() == writeData);
}

TEST_CASE("WriteRequest throws with too big data", "[WriteRequest]")
{
    int16_t descriptor = 10;
    auto writeData = PlainData(std::vector<std::byte>(WriteRequest::MAX_DATA_SIZE + 1));
    CHECK_THROWS(WriteRequest(descriptor, writeData.getData().data(), writeData.getSize()));
}

TEST_CASE("WriteRequest correctly deserializes", "[WriteRequest]")
{
    int16_t descriptor = 10;
    auto writeData = PlainData({std::byte(0x1), std::byte(0x2)});
    DomainData data;
    int16_t desc = htons(descriptor);
    data.append(&desc, sizeof(desc));
    int16_t dataSize = htons(writeData.getSize());
    data.append(&dataSize, sizeof(dataSize));
    data.append(writeData.getData().data(), writeData.getSize());

    CHECK_NOTHROW(WriteRequest(data));
    WriteRequest req(data);
    CHECK(req.getDescriptor() == descriptor);
    CHECK(req.getWriteData() == writeData);
}

TEST_CASE("WriteRequest deserialization throws with bad message size", "[WriteRequest]")
{
    DomainData data;
    uint8_t something = 5;
    data.append(&something, sizeof(something));

    CHECK_THROWS(WriteRequest(data));
}

TEST_CASE("WriteRequest deserialization throws with too big data", "[WriteRequest]")
{
    int16_t descriptor = 10;
    auto writeData = PlainData(std::vector<std::byte>(WriteRequest::MAX_DATA_SIZE + 1));
    DomainData data;
    int16_t desc = htons(descriptor);
    data.append(&desc, sizeof(desc));
    int16_t dataSize = htons(writeData.getSize());
    data.append(&dataSize, sizeof(dataSize));
    data.append(writeData.getData().data(), writeData.getSize());

    CHECK_THROWS(WriteRequest(data));
}

TEST_CASE("WriteRequest correctly serializes", "[WriteRequest]")
{
    int16_t descriptor = 10;
    auto writeData = PlainData({std::byte(0x1), std::byte(0x2)});
    auto data = WriteRequest(descriptor, writeData.getData().data(), writeData.getSize()).serialize();

    DomainData expectedData;
    int16_t desc = htons(descriptor);
    expectedData.append(&desc, sizeof(desc));
    int16_t dataSize = htons(writeData.getSize());
    expectedData.append(&dataSize, sizeof(dataSize));
    expectedData.append(writeData.getData().data(), writeData.getSize());

    CHECK(data == expectedData);
}
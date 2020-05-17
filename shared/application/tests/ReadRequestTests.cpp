#include <catch.hpp>
#include <netinet/in.h>

#include "application/mynfs/requests/ReadRequest.h"

TEST_CASE("ReadRequest correctly constructs from arguments", "[ReadRequest]")
{
    int16_t descriptor = 10;
    int16_t count = 123;
    CHECK_NOTHROW(ReadRequest(descriptor, count));
    ReadRequest req(descriptor, count);
    CHECK(req.getDescriptor() == descriptor);
    CHECK(req.getCount() == count);
}

TEST_CASE("ReadRequest throws with too big count", "[ReadRequest]")
{
    int16_t descriptor = 10;
    int16_t count = ReadRequest::MAX_DATA_SIZE + 1;
    CHECK_THROWS(ReadRequest(descriptor, count));
}

TEST_CASE("ReadRequest correctly deserializes", "[ReadRequest]")
{
    int16_t descriptor = 10;
    int16_t count = 123;

    DomainData data;
    int16_t desc = htons(descriptor);
    data.append(&desc, sizeof(desc));
    int16_t cnt = htons(count);
    data.append(&cnt, sizeof(cnt));

    CHECK_NOTHROW(ReadRequest(data));
    ReadRequest req(data);
    CHECK(req.getDescriptor() == descriptor);
    CHECK(req.getCount() == count);
}

TEST_CASE("ReadRequest deserialization throws with bad message size", "[ReadRequest]")
{
    DomainData data;
    uint8_t something = 5;
    data.append(&something, sizeof(something));

    CHECK_THROWS(ReadRequest(data));
}

TEST_CASE("ReadRequest deserialization throws with too big count", "[ReadRequest]")
{
    int16_t descriptor = 10;
    int16_t count = ReadRequest::MAX_DATA_SIZE + 1;

    DomainData data;
    int16_t desc = htons(descriptor);
    data.append(&desc, sizeof(desc));
    int16_t cnt = htons(count);
    data.append(&cnt, sizeof(cnt));

    CHECK_THROWS(ReadRequest(data));
}

TEST_CASE("ReadRequest correctly serializes", "[ReadRequest]")
{
    int16_t descriptor = 10;
    int16_t count = 123;
    auto data = ReadRequest(descriptor, count).serialize();

    DomainData expectedData;
    int16_t desc = htons(descriptor);
    expectedData.append(&desc, sizeof(desc));
    int16_t cnt = htons(count);
    expectedData.append(&cnt, sizeof(cnt));

    CHECK(data == expectedData);
}
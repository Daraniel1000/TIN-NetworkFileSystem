#include <catch.hpp>
#include <netinet/in.h>

#include "application/mynfs/requests/LseekRequest.h"

TEST_CASE("LseekRequest correctly constructs from arguments", "[LseekRequest]")
{
    int16_t descriptor = 10;
    int32_t offset = 124;
    int8_t whence = SEEK_SET;
    CHECK_NOTHROW(LseekRequest(descriptor, offset, whence));
    LseekRequest req(descriptor, offset, whence);
    CHECK(req.getDescriptor() == descriptor);
    CHECK(req.getOffset() == offset);
    CHECK(req.getWhence() == whence);
}

TEST_CASE("LseekRequest throws with bad whence", "[LseekRequest]")
{
    int16_t descriptor = 10;
    int32_t offset = 124;
    int8_t whence = SEEK_HOLE;
    CHECK_THROWS(LseekRequest(descriptor, offset, whence));
}

TEST_CASE("LseekRequest correctly deserializes", "[LseekRequest]")
{
    int16_t descriptor = 10;
    int32_t offset = 124;
    int8_t whence = SEEK_SET;

    DomainData data;
    int16_t desc = htons(descriptor);
    data.append(&desc, sizeof(desc));
    int32_t off = htonl(offset);
    data.append(&off, sizeof(off));
    data.append(&whence, sizeof(whence));

    CHECK_NOTHROW(LseekRequest(data));
    LseekRequest req(data);
    CHECK(req.getDescriptor() == descriptor);
    CHECK(req.getOffset() == offset);
    CHECK(req.getWhence() == whence);
}

TEST_CASE("LseekRequest deserialization throws with bad message size", "[LseekRequest]")
{
    DomainData data;
    uint8_t something = 5;
    data.append(&something, sizeof(something));

    CHECK_THROWS(LseekRequest(data));
}

TEST_CASE("LseekRequest deserialization throws with bad whence", "[LseekRequest]")
{
    int16_t descriptor = 10;
    int32_t offset = 124;
    int8_t whence = SEEK_HOLE;

    DomainData data;
    int16_t desc = htons(descriptor);
    data.append(&desc, sizeof(desc));
    int32_t off = htonl(offset);
    data.append(&off, sizeof(off));
    data.append(&whence, sizeof(whence));

    CHECK_THROWS(LseekRequest(data));
}

TEST_CASE("LseekRequest correctly serializes", "[LseekRequest]")
{
    int16_t descriptor = 10;
    int32_t offset = 124;
    int8_t whence = SEEK_SET;
    auto data = LseekRequest(descriptor, offset, whence).serialize();

    DomainData expectedData;
    int16_t desc = htons(descriptor);
    expectedData.append(&desc, sizeof(desc));
    int32_t off = htonl(offset);
    expectedData.append(&off, sizeof(off));
    expectedData.append(&whence, sizeof(whence));

    CHECK(data == expectedData);
}
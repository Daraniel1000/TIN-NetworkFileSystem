#include <catch.hpp>
#include <netinet/in.h>

#include "application/mynfs/requests/CloseRequest.h"

TEST_CASE("CloseRequest correctly constructs from arguments", "[CloseRequest]")
{
    int16_t descriptor = 10;
    CHECK_NOTHROW(CloseRequest(descriptor));
    CloseRequest req(descriptor);
    CHECK(req.getDescriptor() == descriptor);
}

TEST_CASE("CloseRequest correctly deserializes", "[CloseRequest]")
{
    int16_t descriptor = 10;

    DomainData data;
    int16_t desc = htons(descriptor);
    data.append(&desc, sizeof(desc));

    CHECK_NOTHROW(CloseRequest(data));
    CloseRequest req(data);
    CHECK(req.getDescriptor() == descriptor);
}

TEST_CASE("CloseRequest deserialization throws with bad message size", "[CloseRequest]")
{
    DomainData data;
    uint8_t something = 5;
    data.append(&something, sizeof(something));

    CHECK_THROWS(CloseRequest(data));
}

TEST_CASE("CloseRequest correctly serializes", "[CloseRequest]")
{
    int16_t descriptor = 10;
    auto data = CloseRequest(descriptor).serialize();

    DomainData expectedData;
    int16_t desc = htons(descriptor);
    expectedData.append(&desc, sizeof(desc));

    CHECK(data == expectedData);
}
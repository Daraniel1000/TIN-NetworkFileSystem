#include <catch.hpp>
#include <netinet/in.h>

#include "application/mynfs/replies/OpenReply.h"

TEST_CASE("OpenReply correctly constructs from arguments", "[OpenReply]")
{
    int16_t descriptor = 10;
    OpenReplyError error(1);
    CHECK_NOTHROW(OpenReply(descriptor, error));
    OpenReply rep(descriptor, error);
    CHECK(rep.getDescriptor() == descriptor);
    CHECK(rep.getError().getErrorValue() == error.getErrorValue());
}

TEST_CASE("OpenReply correctly deserializes", "[OpenReply]")
{
    DomainData data;
    uint16_t descriptor = htons(10);
    data.append(&descriptor, sizeof(descriptor));
    PlainError error(1);

    CHECK_NOTHROW(OpenReply(data, error));
    OpenReply rep(data, error);
    CHECK(rep.getDescriptor() == ntohs(descriptor));
    CHECK(rep.getError().getErrorValue() == error.getErrorValue());
}

TEST_CASE("OpenReply correctly serializes", "[OpenReply]")
{
    int16_t descriptor = 10;
    OpenReplyError error(1);
    auto data = OpenReply(descriptor, error).getData();

    DomainData expectedData;
    descriptor = htons(10);
    expectedData.append(&descriptor, sizeof(descriptor));

    CHECK(data == expectedData);
}
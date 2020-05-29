#include <catch.hpp>
#include <netinet/in.h>

#include "application/mynfs/replies/LseekReply.h"

TEST_CASE("LseekReply correctly constructs from arguments", "[LseekReply]")
{
    int32_t offset = 10;
    LseekReplyError error(-1);
    CHECK_NOTHROW(LseekReply(offset, error));
    LseekReply rep(offset, error);
    CHECK(rep.getOffset() == offset);
    CHECK(rep.getError().getErrorValue() == error.getErrorValue());
}

TEST_CASE("LseekReply correctly deserializes", "[LseekReply]")
{
    DomainData data;
    int32_t offset = htonl(10);
    data.append(&offset, sizeof(offset));
    PlainError error(99);

    CHECK_NOTHROW(LseekReply(data, error));
    LseekReply rep(data, error);
    CHECK(rep.getOffset() == ntohl(offset));
    CHECK(rep.getError().getErrorValue() == error.getErrorValue());
}

TEST_CASE("LseekReply throws with bad deserialization data size", "[LseekReply]")
{
    DomainData data;
    int32_t offset = htonl(10);
    data.append(&offset, sizeof(offset));
    data.append(&offset, sizeof(offset));
    PlainError error(-1);

    CHECK_THROWS(LseekReply(data, error));
}

TEST_CASE("LseekReply correctly serializes", "[LseekReply]")
{
    int32_t offset = 10;
    LseekReplyError error(-1);
    auto data = LseekReply(offset, error).serialize();

    DomainData expectedData;
    offset = htonl(10);
    expectedData.append(&offset, sizeof(offset));

    CHECK(data == expectedData);
}
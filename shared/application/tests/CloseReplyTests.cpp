#include <catch.hpp>

#include "application/mynfs/replies/CloseReply.h"

TEST_CASE("CloseReply correctly constructs from arguments", "[CloseReply]")
{
    CloseReplyError error(-1);
    CHECK_NOTHROW(CloseReply(error));
    CloseReply rep(error);
    CHECK(rep.getError().getErrorValue() == error.getErrorValue());
}

TEST_CASE("CloseReply correctly deserializes", "[CloseReply]")
{
    DomainData data;
    PlainError error(99);

    CHECK_NOTHROW(CloseReply(data, error));
    CloseReply rep(data, error);
    CHECK(rep.getError().getErrorValue() == error.getErrorValue());
}

TEST_CASE("CloseReply throws with bad deserialization data size", "[CloseReply]")
{
    DomainData data({std::byte(0x0)});
    PlainError error(-1);

    CHECK_THROWS(CloseReply(data, error));
}

TEST_CASE("CloseReply correctly serializes", "[CloseReply]")
{
    CloseReplyError error(-1);
    auto data = CloseReply(error).serialize();

    DomainData expectedData;

    CHECK(data == expectedData);
}
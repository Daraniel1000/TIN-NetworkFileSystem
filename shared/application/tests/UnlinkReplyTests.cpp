#include <catch.hpp>

#include "application/mynfs/replies/UnlinkReply.h"

TEST_CASE("UnlinkReply correctly constructs from arguments", "[UnlinkReply]")
{
    UnlinkReplyError error(1);
    CHECK_NOTHROW(UnlinkReply(error));
    UnlinkReply rep(error);
    CHECK(rep.getError().getErrorValue() == error.getErrorValue());
}

TEST_CASE("UnlinkReply correctly deserializes", "[UnlinkReply]")
{
    DomainData data;
    PlainError error(1);

    CHECK_NOTHROW(UnlinkReply(data, error));
    UnlinkReply rep(data, error);
    CHECK(rep.getError().getErrorValue() == error.getErrorValue());
}

TEST_CASE("UnlinkReply correctly serializes", "[UnlinkReply]")
{
    UnlinkReplyError error(1);
    auto data = UnlinkReply(error).serialize();

    DomainData expectedData;

    CHECK(data == expectedData);
}
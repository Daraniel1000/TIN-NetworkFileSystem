#include <catch.hpp>
#include <netinet/in.h>

#include "application/mynfs/replies/WriteReply.h"

TEST_CASE("WriteReply correctly constructs from arguments", "[WriteReply]")
{
    int16_t count = 10;
    WriteReplyError error(1);
    CHECK_NOTHROW(WriteReply(count, error));
    WriteReply rep(count, error);
    CHECK(rep.getCount() == count);
    CHECK(rep.getError().getErrorValue() == error.getErrorValue());
}

TEST_CASE("WriteReply throws with too big count", "[WriteReply]")
{
    int16_t count = WriteReply::MAX_DATA_SIZE + 1;
    WriteReplyError error(1);
    CHECK_THROWS(WriteReply(count, error));
}

TEST_CASE("WriteReply correctly deserializes", "[WriteReply]")
{
    DomainData data;
    int16_t count = htons(10);
    data.append(&count, sizeof(count));
    PlainError error(1);

    CHECK_NOTHROW(WriteReply(data, error));
    WriteReply rep(data, error);
    CHECK(rep.getCount()== ntohs(count));
    CHECK(rep.getError().getErrorValue() == error.getErrorValue());
}

TEST_CASE("WriteReply throws with too big data when deserializing", "[WriteReply]")
{
    DomainData data;
    int16_t count = htons(WriteReply::MAX_DATA_SIZE + 1);
    data.append(&count, sizeof(count));
    PlainError error(1);

    CHECK_THROWS(WriteReply(data, error));
}

TEST_CASE("WriteReply correctly serializes", "[WriteReply]")
{
    int16_t count = 10;
    WriteReplyError error(1);
    auto data = WriteReply(count, error).serialize();

    DomainData expectedData;
    count = htons(10);
    expectedData.append(&count, sizeof(count));

    CHECK(data == expectedData);
}
#include <catch.hpp>
#include <netinet/in.h>

#include "application/mynfs/requests/UnlinkRequest.h"

TEST_CASE("UnlinkRequest correctly constructs from arguments", "[UnlinkRequest]")
{
    std::string path = "/dir/";
    CHECK_NOTHROW(UnlinkRequest(path.data()));
    UnlinkRequest req(path.data());
    CHECK(req.getPath() == path);
}

TEST_CASE("UnlinkRequest throws with too long path", "[UnlinkRequest]")
{
    std::string path(UnlinkRequest::MAX_PATH_SIZE + 1, '.');
    CHECK_THROWS(UnlinkRequest(path.data()));
}

TEST_CASE("UnlinkRequest correctly deserializes", "[UnlinkRequest]")
{
    std::string path = "/dir/";

    DomainData data;
    int16_t pathLength = htons(path.size());
    data.append(&pathLength, sizeof(pathLength));
    data.append(path.data(), path.size());

    CHECK_NOTHROW(UnlinkRequest(data));
    UnlinkRequest req(data);
    CHECK(req.getPath() == path);
}

TEST_CASE("UnlinkRequest deserialization throws with bad message size", "[UnlinkRequest]")
{
    DomainData data;
    uint8_t something = 5;
    data.append(&something, sizeof(something));

    CHECK_THROWS(UnlinkRequest(data));
}

TEST_CASE("UnlinkRequest deserialization throws with too long path", "[UnlinkRequest]")
{
    std::string path(UnlinkRequest::MAX_PATH_SIZE + 1, '.');

    DomainData data;
    int16_t pathLength = path.size();
    data.append(&pathLength, sizeof(pathLength));
    data.append(path.data(), path.size());

    CHECK_THROWS(UnlinkRequest(data));
}

TEST_CASE("UnlinkRequest correctly serializes", "[UnlinkRequest]")
{
    std::string path = "/dir/";
    auto data = UnlinkRequest(path.data()).serialize();

    DomainData expectedData;
    int16_t pathLength = htons(path.size());
    expectedData.append(&pathLength, sizeof(pathLength));
    expectedData.append(path.data(), path.size());

    CHECK(data == expectedData);
}
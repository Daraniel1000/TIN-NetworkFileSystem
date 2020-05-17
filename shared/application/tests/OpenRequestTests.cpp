#include <catch.hpp>
#include <fcntl.h>
#include <netinet/in.h>

#include "application/mynfs/requests/OpenRequest.h"

TEST_CASE("OpenRequest correctly constructs from arguments", "[OpenRequest]")
{
    std::string path = "/dir/";
    CHECK_NOTHROW(OpenRequest(path.data(), O_RDONLY));
    OpenRequest req(path.data(), O_RDONLY);
    CHECK(req.getOflag() == O_RDONLY);
    CHECK(req.getPath() == path);
}

TEST_CASE("OpenRequest throws with invalid oflag", "[OpenRequest]")
{
    std::string path = "/dir/";
    CHECK_THROWS(OpenRequest(path.data(), O_ACCMODE));
}

TEST_CASE("OpenRequest throws with too long path", "[OpenRequest]")
{
    std::string path(OpenRequest::MAX_PATH_SIZE + 1, '.');
    CHECK_THROWS(OpenRequest(path.data(), O_RDONLY));
}

TEST_CASE("OpenRequest correctly deserializes", "[OpenRequest]")
{
    std::string path = "/dir/";

    DomainData data;
    uint16_t oFlag = htons(O_RDONLY);
    data.append(&oFlag, sizeof(oFlag));
    int16_t pathLength = htons(path.size());
    data.append(&pathLength, sizeof(pathLength));
    data.append(path.data(), path.size());

    CHECK_NOTHROW(OpenRequest(data));
    OpenRequest req(data);
    CHECK(req.getOflag() == O_RDONLY);
    CHECK(req.getPath() == path);
}

TEST_CASE("OpenRequest deserialization throws with bad message size", "[OpenRequest]")
{
    DomainData data;
    uint8_t something = 5;
    data.append(&something, sizeof(something));

    CHECK_THROWS(OpenRequest(data));
}

TEST_CASE("OpenRequest deserialization throws with bad oflag", "[OpenRequest]")
{
    std::string path = "/dir/";

    DomainData data;
    uint16_t oFlag = htons(O_ACCMODE);
    data.append(&oFlag, sizeof(oFlag));
    int16_t pathLength = htons(path.size());
    data.append(&pathLength, sizeof(pathLength));
    data.append(path.data(), path.size());

    CHECK_THROWS(OpenRequest(data));
}

TEST_CASE("OpenRequest deserialization throws with too long path", "[OpenRequest]")
{
    std::string path(OpenRequest::MAX_PATH_SIZE + 1, '.');

    DomainData data;
    uint16_t oFlag = htons(O_RDONLY);
    data.append(&oFlag, sizeof(oFlag));
    int16_t pathLength = path.size();
    data.append(&pathLength, sizeof(pathLength));
    data.append(path.data(), path.size());

    CHECK_THROWS(OpenRequest(data));
}

TEST_CASE("OpenRequest correctly serializes", "[OpenRequest]")
{
    std::string path = "/dir/";
    auto data = OpenRequest(path.data(), O_RDONLY).serialize();

    DomainData expectedData;
    uint16_t oFlag = htons(O_RDONLY);
    expectedData.append(&oFlag, sizeof(oFlag));
    int16_t pathLength = htons(path.size());
    expectedData.append(&pathLength, sizeof(pathLength));
    expectedData.append(path.data(), path.size());

    CHECK(data == expectedData);
}
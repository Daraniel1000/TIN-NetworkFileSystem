#include <catch.hpp>
#include <fff.h>

#include "transport/PlainData.h"


TEST_CASE("PlainData correctly constructing", "[PlainData]")
{
    std::vector<std::byte> dummyData = {std::byte(0x1), std::byte(0x2), std::byte(0x3)};

    CHECK_NOTHROW(PlainData(dummyData.data(), dummyData.size()));
}

TEST_CASE("PlainData holds correct value", "[PlainData]")
{
    std::vector<std::byte> dummyData = {std::byte(0x1), std::byte(0x2), std::byte(0x3)};

    auto data = PlainData(dummyData.data(), dummyData.size());

    CHECK(data.getData() == dummyData);
}
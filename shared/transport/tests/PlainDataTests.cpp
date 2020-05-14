#include <catch.hpp>

#include "transport/PlainData.h"


TEST_CASE("PlainData correctly constructing", "[PlainData]")
{
    std::vector<std::byte> dummyData = {std::byte(0x1), std::byte(0x2), std::byte(0x3)};

    CHECK_NOTHROW(PlainData(dummyData.data(), dummyData.size()));
}

TEST_CASE("PlainData correctly constructing with empty data", "[PlainData]")
{
    std::vector<std::byte> dummyData;

    CHECK_NOTHROW(PlainData(dummyData.data(), dummyData.size()));
}

TEST_CASE("PlainData holds correct value", "[PlainData]")
{
    std::vector<std::byte> dummyData = {std::byte(0x1), std::byte(0x2), std::byte(0x3)};

    auto data = PlainData(dummyData.data(), dummyData.size());

    CHECK(data.getData() == dummyData);
}

TEST_CASE("PlainData appending correctly to empty", "[PlainData]")
{
    std::vector<std::byte> dummyData = {std::byte(0x1), std::byte(0x2), std::byte(0x3)};

    auto data = PlainData();
    data.append(dummyData.data(), dummyData.size());

    CHECK(data.getData() == dummyData);
}

TEST_CASE("PlainData appending correctly to non-empty", "[PlainData]")
{
    std::vector<std::byte> dummyData1 = {std::byte(0x1), std::byte(0x2), std::byte(0x3)};
    std::vector<std::byte> dummyData2 = {std::byte(0x4), std::byte(0x5), std::byte(0x6)};

    auto data = PlainData(dummyData1.data(), dummyData1.size());
    data.append(dummyData2.data(), dummyData2.size());

    dummyData1.insert(dummyData1.end(), dummyData2.begin(), dummyData2.end());

    CHECK(data.getData() == dummyData1);
}

TEST_CASE("PlainData holding copy of data", "[PlainData]")
{
    std::vector<std::byte> dummyData = {std::byte(0x1), std::byte(0x2), std::byte(0x3)};

    auto data = PlainData(dummyData.data(), dummyData.size());

    dummyData.clear();

    CHECK(data.getData() != dummyData);
}
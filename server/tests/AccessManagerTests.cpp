#include <catch.hpp>
#include <fstream>

#include "../src/AccessManager.h"

TEST_CASE("Access manager checking hosts permission", "[AccessManager]")
{
    std::vector<std::string> hosts {"localhost", "192.168.0.1"};
    std::ofstream of("hosts.txt");
    for(const auto& host : hosts)
        of << host << std::endl;
    AccessManager am(".", "hosts.txt");
    CHECK(am.isPermitted(IpAddress("localhost")));
    CHECK(am.isPermitted(IpAddress("192.168.0.1")));
    CHECK(!am.isPermitted(IpAddress("192.168.0.2")));
}

TEST_CASE("Access manager get bad descriptor", "[AccessManager]")
{
    AccessManager am(".", "hosts.txt");
    CHECK(am.getDescriptor(NetworkAddress("localhost")) == -1);
}

TEST_CASE("Access manager get existing descriptor", "[AccessManager]")
{
    AccessManager am(".", "hosts.txt");
    auto descriptor = am.generateDescriptor(NetworkAddress("localhost"));
    CHECK(am.getDescriptor(NetworkAddress("localhost")) == descriptor);
}

TEST_CASE("Access manager not clearing bad descriptor", "[AccessManager]")
{
    AccessManager am(".", "hosts.txt");
    CHECK(!am.clearDescriptor(NetworkAddress("localhost")));
}

TEST_CASE("Access manager clears descriptor", "[AccessManager]")
{
    AccessManager am(".", "hosts.txt");
    am.generateDescriptor(NetworkAddress("localhost"));
    CHECK(am.clearDescriptor(NetworkAddress("localhost")));
}

TEST_CASE("Access manager generates descriptors", "[AccessManager]")
{
    AccessManager am(".", "hosts.txt");
    auto d1 = am.generateDescriptor(NetworkAddress("localhost"));
    auto d2 = am.generateDescriptor(NetworkAddress("192.168.0.1"));
    CHECK(am.getDescriptor(NetworkAddress("localhost")) == d1);
    CHECK(am.getDescriptor(NetworkAddress("192.168.0.1")) == d2);
}

TEST_CASE("Access manager can't generate new descriptors twice", "[AccessManager]")
{
    AccessManager am(".", "hosts.txt");
    auto d1 = am.generateDescriptor(NetworkAddress("localhost"));
    auto d2 = am.generateDescriptor(NetworkAddress("localhost"));
    CHECK(d1 == d2);
    CHECK(am.getDescriptor(NetworkAddress("localhost")) == d1);
}

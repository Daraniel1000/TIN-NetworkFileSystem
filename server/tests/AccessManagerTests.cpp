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
    CHECK(am.getSystemDescriptor(NetworkAddress("localhost"), 1) == -1);
}

TEST_CASE("Access manager get existing descriptor", "[AccessManager]")
{
    AccessManager am(".", "hosts.txt");
    auto descriptor = am.generateAppDescriptor(NetworkAddress("localhost"), 3);
    CHECK(am.getSystemDescriptor(NetworkAddress("localhost"), descriptor) == 3);
}

TEST_CASE("Access manager not clearing bad descriptor", "[AccessManager]")
{
    AccessManager am(".", "hosts.txt");
    CHECK(!am.clearAppDescriptor(NetworkAddress("localhost"), 1));
}

TEST_CASE("Access manager clears descriptor", "[AccessManager]")
{
    AccessManager am(".", "hosts.txt");
    auto d = am.generateAppDescriptor(NetworkAddress("localhost"), 3);
    CHECK(am.clearAppDescriptor(NetworkAddress("localhost"), d));
}

TEST_CASE("Access manager generates descriptors", "[AccessManager]")
{
    AccessManager am(".", "hosts.txt");
    auto d1 = am.generateAppDescriptor(NetworkAddress("localhost"), 3);
    auto d2 = am.generateAppDescriptor(NetworkAddress("192.168.0.1"), 4);
    CHECK(am.getSystemDescriptor(NetworkAddress("localhost"), d1) == 3);
    CHECK(am.getSystemDescriptor(NetworkAddress("192.168.0.1"), d2) == 4);
}

TEST_CASE("Access manager can't generate new descriptors twice", "[AccessManager]")
{
    AccessManager am(".", "hosts.txt");
    auto d1 = am.generateAppDescriptor(NetworkAddress("localhost"), 3);
    auto d2 = am.generateAppDescriptor(NetworkAddress("localhost"), 3);
    CHECK(d1 == d2);
    CHECK(am.getSystemDescriptor(NetworkAddress("localhost"), d1) == 3);
}

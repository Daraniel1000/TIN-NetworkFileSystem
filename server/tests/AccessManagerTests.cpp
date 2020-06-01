#include <catch.hpp>
#include <fstream>

#include "../src/AccessManager.h"

TEST_CASE("Access manager checking hosts permission", "[AccessManager]")
{
    std::vector<std::string> hosts {"localhost", "192.168.0.1"};
    std::ofstream of("./testDir/hosts.txt");
    for(const auto& host : hosts)
        of << host << std::endl;
    AccessManager am("./testDir", "root", "hosts.txt");
    CHECK(am.isPermitted(IpAddress("localhost")));
    CHECK(am.isPermitted(IpAddress("192.168.0.1")));
    CHECK(!am.isPermitted(IpAddress("192.168.0.2")));
}

TEST_CASE("Access manager get bad descriptor", "[AccessManager]")
{
    AccessManager am("./testDir","root", "hosts.txt");
    CHECK(am.getSystemDescriptor(IpAddress("localhost"), 1) == -1);
}

TEST_CASE("Access manager get existing descriptor", "[AccessManager]")
{
    AccessManager am("./testDir", "root","hosts.txt");
    auto descriptor = am.generateAppDescriptor(IpAddress("localhost"), 3);
    CHECK(am.getSystemDescriptor(IpAddress("localhost"), descriptor) == 3);
}

TEST_CASE("Access manager not clearing bad descriptor", "[AccessManager]")
{
    AccessManager am("./testDir", "root","hosts.txt");
    CHECK(!am.clearAppDescriptor(IpAddress("localhost"), 1));
}

TEST_CASE("Access manager clears descriptor", "[AccessManager]")
{
    AccessManager am("./testDir", "root","hosts.txt");
    auto d = am.generateAppDescriptor(IpAddress("localhost"), 3);
    CHECK(am.clearAppDescriptor(IpAddress("localhost"), d));
}

TEST_CASE("Access manager generates descriptors", "[AccessManager]")
{
    AccessManager am("./testDir", "root","hosts.txt");
    auto d1 = am.generateAppDescriptor(IpAddress("localhost"), 3);
    auto d2 = am.generateAppDescriptor(IpAddress("192.168.0.1"), 4);
    CHECK(am.getSystemDescriptor(IpAddress("localhost"), d1) == 3);
    CHECK(am.getSystemDescriptor(IpAddress("192.168.0.1"), d2) == 4);
}

TEST_CASE("Access manager can't generate new descriptors twice", "[AccessManager]")
{
    AccessManager am("./testDir", "root", "hosts.txt");
    auto d1 = am.generateAppDescriptor(IpAddress("localhost"), 3);
    auto d2 = am.generateAppDescriptor(IpAddress("localhost"), 3);
    CHECK(d1 == d2);
    CHECK(am.getSystemDescriptor(IpAddress("localhost"), d1) == 3);
}

TEST_CASE("Access manager check good path", "[AccessManager]")
{
    AccessManager am("./testDir", "root", "hosts.txt");
    CHECK(am.isPathPermitted("dir/file.txt"));
}

TEST_CASE("Access manager check bad path", "[AccessManager]")
{
    AccessManager am("./testDir", "root", "hosts.txt");
    CHECK(!am.isPathPermitted("./dir/../../../file.txt"));
}
#include <catch.hpp>
#include <fff.h>
#include <addresses/IpAddress.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <addresses/NetworkAddress.h>
#include "addresses/AnyAddress.h"
#include "addresses/LocalAddress.h"
#include "addresses/EphemeralPort.h"


TEST_CASE("Numeric address correctly converted", "[IpAddress]")
{
    struct in_addr inaddr;
    inet_pton(AF_INET, "127.0.0.1", &inaddr);
    IpAddress ip("127.0.0.1");

    CHECK(ip.toHostOrder() == ntohl(inaddr.s_addr));
}

TEST_CASE("Domain name correctly converted", "[IpAddress]")
{
    uint32_t address;
    char buf[INET_ADDRSTRLEN];
    IpAddress ip("google.com");
    struct hostent *h;
    h = gethostbyname("google.com");

    memset(&address, 0, sizeof(address));
    memcpy(&address, h->h_addr,h->h_length);

    CHECK(ip.toHostOrder() == ntohl(address));
}

TEST_CASE("Not valid domain name throw exception", "[IpAddress]")
{
    CHECK_THROWS(IpAddress("aloha"));
}

TEST_CASE("Not valid ip address throw exception", "[IpAddress]")
{
    CHECK_THROWS(IpAddress("555.23.456.3"));
}

TEST_CASE("Construct NetworkAddress from string without port", "[NetworkAddress]")
{
    char address[] = "192.168.24.21";
    NetworkAddress netAddress(address);
    CHECK(netAddress.getPort().toHostOrder() == 0);
    CHECK(IpAddress("192.168.24.21").toHostOrder() == netAddress.getAddress().toHostOrder());
}
TEST_CASE("Construct NetworkAddress from string", "[NetworkAddress]")
{
    char address[] = "192.168.24.21:22";
    NetworkAddress netAddress(address);
    CHECK(netAddress.getPort().toHostOrder() == 22);
    CHECK(IpAddress("192.168.24.21").toHostOrder() == netAddress.getAddress().toHostOrder());
}
TEST_CASE("Construct NetworkAddress from string with colon, but without port", "[NetworkAddress]")
{
    char address[] = "192.168.24.21:";
    NetworkAddress netAddress(address);
    CHECK(netAddress.getPort().toHostOrder() == 0);
    CHECK(IpAddress("192.168.24.21").toHostOrder() == netAddress.getAddress().toHostOrder());
}

TEST_CASE("Address toString()", "[NetworkAddress]")
{
    sockaddr_in str = NetworkAddress(IpAddress("192.168.24.21"), Port(22)).toStruct();
    CHECK(str.sin_port == htons(22));
    CHECK(NetworkAddress(IpAddress("192.168.24.21"), Port(22)).toString() == "192.168.24.21:22");
}

TEST_CASE("Address toStruct()", "[NetworkAddress]")
{
    sockaddr_in str = NetworkAddress(IpAddress("192.168.24.21"), Port(22)).toStruct();
    CHECK(str.sin_port == htons(22));
    CHECK(str.sin_addr.s_addr == IpAddress("192.168.24.21").toNetworkOrder());
    CHECK(str.sin_family == AF_INET);
}

TEST_CASE("AnyAddress() is equal to IpAddress(INADDR_ANY)", "[AnyAddress]")
{
    CHECK(AnyAddress().toHostOrder() == IpAddress(INADDR_ANY).toHostOrder());
}

TEST_CASE("LocalAddress() is equal to IpAddress('127.0.0.1')", "[LocalAddress]")
{
    CHECK(LocalAddress().toHostOrder() == IpAddress("127.0.0.1").toHostOrder());
}

TEST_CASE("EphemeralPort() is equal to Port(0)", "[EphemeralPort]")
{
    CHECK(EphemeralPort().toHostOrder() == Port(0).toHostOrder());
}
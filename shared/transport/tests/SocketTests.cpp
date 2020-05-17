#include <catch.hpp>
#include <thread>
#include <cstddef>
#include <transport/read_interrupted_error.h>

#include "transport/socket/UDPSocket.h"
#include "addresses/EphemeralPort.h"

TEST_CASE("Socket correctly constructs on implicit ephemeral port", "[UDPSocket]")
{
    CHECK_NOTHROW(UDPSocket(EphemeralPort()));
}

TEST_CASE("Socket not constructing on explicit ephemeral port", "[UDPSocket]")
{
    CHECK_NOTHROW(UDPSocket(Port(54321)));
}

TEST_CASE("Socket not constructing on reserved port", "[UDPSocket]")
{
    CHECK_THROWS(UDPSocket(Port(22)));
}

TEST_CASE("Socket correct communication with normal data", "[UDPSocket]")
{
    PlainData dummyData({std::byte(0x1), std::byte(0x2), std::byte(0x3)});
    uint16_t port = 54321;
    uint32_t address = 2130706433; // 127.0.0.1

    UDPSocket sendSocket((EphemeralPort()));
    UDPSocket receiveSocket((Port(port)));

    NetworkAddress receiveAddress((IpAddress(address)), Port(port));
    sendSocket.send(receiveAddress, dummyData);
    NetworkAddress sourceAddress{};
    auto data = receiveSocket.receive(sourceAddress);

    CHECK(data == dummyData);
}

TEST_CASE("Socket correct communication with empty data", "[UDPSocket]")
{
    PlainData dummyData;
    uint16_t port = 54321;
    uint32_t address = 2130706433; // 127.0.0.1

    UDPSocket sendSocket((EphemeralPort()));
    UDPSocket receiveSocket((Port(port)));

    NetworkAddress receiveAddress((IpAddress(address)), Port(port));
    sendSocket.send(receiveAddress, dummyData);
    NetworkAddress sourceAddress{};
    auto data = receiveSocket.receive(sourceAddress);

    CHECK(data == dummyData);
}

TEST_CASE("Socket send throws when message is too big", "[UDPSocket]")
{
    PlainData dummyData(std::vector<std::byte>(UDPSocket::MAX_DATA_SIZE + 1));
    uint16_t port = 54321;
    uint32_t address = 2130706433; // 127.0.0.1

    UDPSocket sendSocket((EphemeralPort()));
    UDPSocket receiveSocket((Port(port)));

    NetworkAddress receiveAddress((IpAddress(address)), Port(port));

    CHECK_THROWS(sendSocket.send(receiveAddress, dummyData));
}

TEST_CASE("Socket send throws with bad recipient", "[UDPSocket]")
{
    PlainData dummyData(std::vector<std::byte>(UDPSocket::MAX_DATA_SIZE + 1));

    UDPSocket sendSocket((EphemeralPort()));

    NetworkAddress receiveAddress((IpAddress()), Port());

    CHECK_THROWS(sendSocket.send(receiveAddress, dummyData));
}

TEST_CASE("Socket wakes up after signal", "[UDPSocket]")
{
    UDPSocket s((EphemeralPort()));
    NetworkAddress sourceAddress{};

    std::thread thread([&]{
        try{ s.receive(sourceAddress);}
        catch (read_interrupted_error&) {}
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    s.signal();
    thread.join();
}
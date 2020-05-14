#include <catch.hpp>
#include <fff.h>

#include "transport/socket/UDPSocket.h"

FAKE_VALUE_FUNC(int, select, int, fd_set*, fd_set*, fd_set*, struct timeval *);
FAKE_VALUE_FUNC(ssize_t, recvfrom, int, void*, size_t, int, struct sockaddr *, socklen_t*);

int select_custom_fake(int socket, fd_set* read_set, fd_set*, fd_set*, struct timeval *)
{
    FD_ZERO(read_set);
    FD_SET(socket-1, read_set);
    return 1;
}

std::vector<std::byte> dummyData;
sockaddr_in dummyAddress;

ssize_t recvfrom_custom_fake(int, void* buffer, size_t, int, struct sockaddr * address, socklen_t*)
{
    memcpy(buffer, dummyData.data(), dummyData.size());
    memcpy(address, &dummyAddress, sizeof(dummyAddress));
    return dummyData.size();
}

TEST_CASE("Socket receives correct data", "[UDPSocket]")
{
    dummyData = {std::byte(0x1), std::byte(0x2), std::byte(0x3)};
    dummyAddress.sin_port = 100;
    dummyAddress.sin_addr.s_addr = 1234;

    select_fake.custom_fake = select_custom_fake;
    recvfrom_fake.custom_fake = recvfrom_custom_fake;

    UDPSocket s(Port(0));
    NetworkAddress sourceAddress;
    auto data = s.receive(sourceAddress);

    CHECK(data.getData() == dummyData);
}

FAKE_VALUE_FUNC(ssize_t , sendto, int, const void*, size_t, int, const struct sockaddr *, socklen_t);

TEST_CASE("Socket writes correct data", "[UDPSocket]")
{
    dummyData = {std::byte(0x1), std::byte(0x2), std::byte(0x3)};
    dummyAddress.sin_port = 100;
    dummyAddress.sin_addr.s_addr = 1234;

    UDPSocket s(Port(0));
    NetworkAddress sourceAddress(IpAddress(dummyAddress.sin_addr.s_addr), Port(dummyAddress.sin_port));
    PlainData dataToSend(dummyData.data(), dummyData.size());
    s.send(sourceAddress, dataToSend);

    auto buf = static_cast<const std::byte*>(sendto_fake.arg1_val);
    auto size = sendto_fake.arg2_val;

    CHECK(dummyData == std::vector<std::byte>(buf, buf + size));
}
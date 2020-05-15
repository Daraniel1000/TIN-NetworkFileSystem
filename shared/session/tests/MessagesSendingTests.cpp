#include <catch.hpp>

#include "addresses/EphemeralPort.h"
#include "transport/socket/UDPSocket.h"

#include "session/messages/ConfirmMessage.h"
#include "session/messages/RequestMessage.h"
#include "session/messages/DataMessage.h"

PlainData send(const PlainData& data)
{
    uint16_t port = 54321;
    uint32_t address = 2130706433; // 127.0.0.1
    UDPSocket sendSocket((EphemeralPort()));
    UDPSocket receiveSocket((Port(port)));

    NetworkAddress receiveAddress((IpAddress(address)), Port(port));
    sendSocket.send(receiveAddress, data);

    NetworkAddress sourceAddress{};
    return receiveSocket.receive(sourceAddress);
}

TEST_CASE("RequestMessage is correctly sent through socket", "[MessagesSending]")
{
    auto msg = RequestMessage();
    auto data = send(msg.serialize());

    CHECK_NOTHROW(RequestMessage(data));
}

TEST_CASE("ConfirmMessage is correctly sent through socket", "[MessagesSending]")
{
    auto msg = ConfirmMessage(PlainError(10));
    auto data = send(msg.serialize());

    CHECK_NOTHROW(ConfirmMessage(data));
    CHECK(ConfirmMessage(data) == msg);
}

TEST_CASE("DataMessage is correctly sent through socket", "[MessagesSending]")
{
    auto argReqType = 1;
    auto argData = DomainData({std::byte(0x1), std::byte(0x2)});
    auto argError = PlainError(0);

    auto msg = DataMessage(argReqType, argData, argError);
    auto data = send(msg.serialize());

    CHECK_NOTHROW(DataMessage(data));
    CHECK(DataMessage(data) == msg);
}

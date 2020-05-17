#include <catch.hpp>
#include <fcntl.h>
#include <transport/socket/UDPSocket.h>
#include <session/messages/ConfirmMessage.h>
#include <session/messages/DataMessage.h>
#include <application/mynfs/replies/Reply.h>
#include <thread>
#include <application/mynfs/replies/OpenReply.h>

#include "mynfslib.h"

const auto serverPort = 54321;
const auto serverAddress = "127.0.0.1:" + std::to_string(serverPort);

void mock_server(const Reply &mockRep)
{
    UDPSocket serverSocket(serverPort);

    NetworkAddress source{};
    serverSocket.receive(source); // get request and ignore
    serverSocket.send(source, ConfirmMessage().serialize()); // send confirm
    auto dataMsg = DataMessage(serverSocket.receive(source)); // get data
    serverSocket.send(source,DataMessage(
                                                 dataMsg.getType(),
                                                 mockRep.serialize(),
                                                 mockRep.getError().serialize()
                                                 ).serialize()); // send reply
    serverSocket.receive(source); // get confirm and ignore
}

TEST_CASE("mynfs_open working correctly", "[mynfs]")
{
    OpenReply rep(10, OpenReplyError(0));

    std::thread thread([&] {
        mock_server(rep);
    });

    auto descriptor = mynfs_open(serverAddress.data(), "/dir/file", O_RDONLY);

    CHECK(descriptor == rep.getDescriptor());

    thread.join();
}
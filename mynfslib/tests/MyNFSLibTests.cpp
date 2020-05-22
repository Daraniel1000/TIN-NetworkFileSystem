#include <catch.hpp>
#include <fcntl.h>
#include <transport/socket/UDPSocket.h>
#include <session/messages/ConfirmMessage.h>
#include <session/messages/DataMessage.h>
#include <application/mynfs/replies/Reply.h>
#include <thread>
#include <application/mynfs/replies/OpenReply.h>
#include <mutex>
#include <condition_variable>

#include "mynfslib.h"

std::mutex m;
std::condition_variable cv;
bool serverReady = false;

const auto serverPort = 54321; // assuming it's not already in use
const auto serverAddress = "localhost:" + std::to_string(serverPort);

void mock_server(const Reply &mockRep)
{
    UDPSocket serverSocket(serverPort);

    // notify creating server
    {
        std::lock_guard<std::mutex> lk(m);
        serverReady = true;
    }
    cv.notify_one();

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
    // expected reply
    OpenReply rep(10, OpenReplyError(0));

    // mock server on another thread
    std::thread thread([&] {
        mock_server(rep);
    });

    // wait for server to start
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, []{return serverReady;});

    // call function
    auto descriptor = mynfs_open(serverAddress.data(), "/path/whatever", O_RDONLY);

    // check if values match
    CHECK(descriptor == rep.getDescriptor());

    // join server thread
    thread.join();
}
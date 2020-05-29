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
#include <application/mynfs/replies/CloseReply.h>
#include <application/mynfs/replies/ReadReply.h>
#include <application/mynfs/replies/WriteReply.h>
#include <application/mynfs/replies/LseekReply.h>
#include <application/mynfs/replies/UnlinkReply.h>

#include "mynfslib.h"

const auto serverPort = 54321; // assuming it's not already in use
const auto serverAddress = "localhost:" + std::to_string(serverPort);

void mock_server(const Reply &mockRep, std::mutex& m, std::condition_variable& cv, bool& serverReady)
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
    std::mutex m;
    std::condition_variable cv;
    bool serverReady = false;
    OpenReply rep(10, OpenReplyError(0));

    // mock server on another thread
    std::thread thread([&] {
        mock_server(rep, m, cv, serverReady);
    });

    // wait for server to start
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [&]{return serverReady;});

    // call function
    auto descriptor = mynfs_open(serverAddress.data(), "/path/whatever", O_RDONLY);

    // check if values match
    CHECK(descriptor == rep.getDescriptor());

    // join server thread
    thread.join();
}

TEST_CASE("mynfs_read working correctly", "[mynfs]")
{
    // expected reply
    std::mutex m;
    std::condition_variable cv;
    bool serverReady = false;

    void* buffer = new char[30];

    ReadReply rep(buffer, 20, ReadReplyError(0));

    // mock server on another thread
    std::thread thread([&] {
        mock_server(rep, m, cv, serverReady);
    });

    // wait for server to start
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [&]{return serverReady;});

    // call function
    auto data = mynfs_read(serverAddress.data(), 1, buffer, 20);
    // check if values match
    CHECK(data == rep.getData().getSize());

    // join server thread
    thread.join();
}


TEST_CASE("mynfs_write working correctly", "[mynfs]")
{
    // expected reply
    std::mutex m;
    std::condition_variable cv;
    bool serverReady = false;

    void* buffer = new char[10];

    WriteReply rep( 10, WriteReplyError(0));

    // mock server on another thread
    std::thread thread([&] {
        mock_server(rep, m, cv, serverReady);
    });

    // wait for server to start
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [&]{return serverReady;});

    // call function
    auto data = mynfs_write(serverAddress.data(), 2, buffer, 10);
    // check if values match
    CHECK(data == rep.getCount());

    // join server thread
    thread.join();
}

TEST_CASE("mynfs_lseek working correctly", "[mynfs]")
{
    // expected reply
    std::mutex m;
    std::condition_variable cv;
    bool serverReady = false;

    LseekReply rep( 2, LseekReplyError(0));

    // mock server on another thread
    std::thread thread([&] {
        mock_server(rep, m, cv, serverReady);
    });

    // wait for server to start
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [&]{return serverReady;});

    // call function
    auto data = mynfs_lseek(serverAddress.data(), 2, 2, 2);
    // check if values match
    CHECK(data == rep.getOffset());

    // join server thread
    thread.join();
}

TEST_CASE("mynfs_close working correctly", "[mynfs]")
{
    // expected reply
    std::mutex m;
    std::condition_variable cv;
    bool serverReady = false;

    CloseReply rep( CloseReplyError(0));

    // mock server on another thread
    std::thread thread([&] {
        mock_server(rep, m, cv, serverReady);
    });

    // wait for server to start
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [&]{return serverReady;});

    // call function
    auto data = mynfs_close(serverAddress.data(), 2);
    // check if values match
    CHECK(data == 0);

    // join server thread
    thread.join();
}

TEST_CASE("mynfs_unlink working correctly", "[mynfs]")
{
    // expected reply
    std::mutex m;
    std::condition_variable cv;
    bool serverReady = false;

    UnlinkReply rep( UnlinkReplyError(0));

    // mock server on another thread
    std::thread thread([&] {
        mock_server(rep, m, cv, serverReady);
    });

    // wait for server to start
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [&]{return serverReady;});

    // call function
    auto data = mynfs_unlink(serverAddress.data(), "path/whatever");
    // check if values match
    CHECK(data == 0);

    // join server thread
    thread.join();
}



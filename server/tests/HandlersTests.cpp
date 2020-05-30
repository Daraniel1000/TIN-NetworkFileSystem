#include <catch.hpp>
#include <fff.h>
#include <fcntl.h>

#include <session/DomainData.h>
#include <session/PlainError.h>
#include <application/mynfs/requests/OpenRequest.h>
#include <application/mynfs/requests/CloseRequest.h>
#include <application//mynfs/requests/ReadRequest.h>
#include <application/mynfs/requests/LseekRequest.h>
#include <application/mynfs/requests/UnlinkRequest.h>
#include <application//mynfs/requests/WriteRequest.h>
#include <zconf.h>
#include "../src/execution/handlers/OpenHandler.h"
#include "../src/execution/handlers/CloseHandler.h"
#include "../src/execution/handlers/ReadHandler.h"
#include "../src/execution/handlers/UnlinkHandler.h"
#include "../src/execution/handlers/LseekHandler.h"
#include "../src/execution/handlers/WriteHandler.h"

TEST_CASE("Creating new file", "[OpenHandler]")
{
    std::string path = "test";
    DomainData replay;
    PlainError replayError;
    OpenHandler handler(DomainData(OpenRequest(path.data(), O_CREAT).serialize()), replay, replayError); //file will be created in server/bin
    handler.handle();
    CHECK(replayError.getErrorValue() == 0);

}

TEST_CASE("File to open does not exist", "[OpenHandler]")
{
    std::string path = "totek.txt";
    DomainData replay;
    PlainError replayError;
    int error = errno;
    OpenHandler handler(DomainData(OpenRequest(path.data(), O_RDONLY).serialize()), replay, replayError);
    handler.handle();
    CHECK(replayError.getErrorValue() == errno);

}

TEST_CASE("Close file", "[CloseHandler]")
{
    std::string path = "test";
    DomainData replay;
    PlainError replayError;
    int fd = open(path.data(),  O_CREAT | O_RDONLY);
    CloseHandler handler(DomainData(CloseRequest(fd).serialize()), replay, replayError);
    handler.handle();
    CHECK(replayError.getErrorValue() == 0);
    close(fd);
    unlink(path.data());
}

TEST_CASE("Close unopened file", "[CloseHandler]")
{
    DomainData replay;
    PlainError replayError;
    int fd = 23;
    CloseHandler handler(DomainData(CloseRequest(fd).serialize()), replay, replayError);
    handler.handle();
    CHECK(replayError.getErrorValue() == EBADF);
}

TEST_CASE("Read file", "[ReadHandler]")
{
    std::string path = "test";
    DomainData replay;
    PlainError replayError;
    int fd = open(path.data(),  O_CREAT | O_RDONLY);
    int count = 20;
    ReadHandler handler(DomainData(ReadRequest(fd, count).serialize()), replay, replayError);
    handler.handle();
    CHECK(replayError.getErrorValue() == 0);
    close(fd);
    unlink(path.data());
}

TEST_CASE("Read unopened file", "[ReadHandler]")
{
    std::string path = "test";
    DomainData replay;
    PlainError replayError;
    int fd = 23;
    int count = 20;
    ReadHandler handler(DomainData(ReadRequest(fd, count).serialize()), replay, replayError);
    handler.handle();
    CHECK(replayError.getErrorValue() == 9);
}

TEST_CASE("Use lseek", "[LseekHandler]")
{
    std::string path = "test";
    DomainData replay;
    PlainError replayError;
    int fd = open(path.data(), O_CREAT | O_RDONLY);
    int offset = 4;
    int whence = SEEK_SET;
    LseekHandler handler(DomainData(LseekRequest(fd, offset, whence).serialize()), replay, replayError);
    handler.handle();
    CHECK(replayError.getErrorValue() == 0);
    close(fd);
    unlink(path.data());
}

TEST_CASE("Lseek on unopened file", "[LseekHandler]")
{
    DomainData replay;
    PlainError replayError;
    int fd = 10;
    int offset = 80;
    int whence = SEEK_END;
    LseekHandler handler(DomainData(LseekRequest(fd, offset, whence).serialize()), replay, replayError);
    handler.handle();
    CHECK(replayError.getErrorValue() == EBADF);
}

TEST_CASE("Write on read only file", "[WriteHandler]")
{
    std::string path = "test";
    DomainData replay;
    PlainError replayError;
    int fd = open(path.data(), O_CREAT | O_RDONLY);
    std::vector<std::byte> data = {std::byte(0x1), std::byte(0x2), std::byte(0x3)};
    PlainData writeData(data);
    int count = 3;
    WriteHandler handler(DomainData(WriteRequest(fd, writeData.getData().data(), writeData.getSize()).serialize()), replay, replayError);
    handler.handle();
    CHECK(replayError.getErrorValue() == EBADF);
    close(fd);
    unlink(path.data());
}

TEST_CASE("Write on write only file", "[WriteHandler]")
{
    std::string path = "test";
    DomainData replay;
    PlainError replayError;
    int fd = open(path.data(), O_CREAT | O_WRONLY);
    std::vector<std::byte> data = {std::byte(0x1), std::byte(0x2), std::byte(0x3)};
    PlainData writeData(data);
    int count = 3;
    WriteHandler handler(DomainData(WriteRequest(fd, writeData.getData().data(), writeData.getSize()).serialize()), replay, replayError);
    handler.handle();
    CHECK(replayError.getErrorValue() == 0);
    close(fd);
    unlink(path.data());
}

TEST_CASE("Unlink on directory path", "[UnlinkHandler]")
{
    std::string path = "../src";
    DomainData replay;
    PlainError replayError;
    UnlinkHandler handler(DomainData(UnlinkRequest(path.data()).serialize()), replay, replayError);
    handler.handle();
    CHECK(replayError.getErrorValue() == EISDIR);
}

TEST_CASE("Unlink file", "[UnlinkHandler]")
{
    std::string path = "test";
    DomainData replay;
    PlainError replayError;
    int fd = open(path.data(), O_CREAT | O_WRONLY);
    UnlinkHandler handler(DomainData(UnlinkRequest(path.data()).serialize()), replay, replayError);
    handler.handle();
    CHECK(replayError.getErrorValue() == 0);
    close(fd);
}
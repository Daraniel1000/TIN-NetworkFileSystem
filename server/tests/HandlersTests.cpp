#include <catch.hpp>
#include <fcntl.h>
#include <unistd.h>
#include <session/DomainData.h>
#include <session/PlainError.h>
#include <application/mynfs/requests/OpenRequest.h>
#include <application/mynfs/requests/CloseRequest.h>
#include <application//mynfs/requests/ReadRequest.h>
#include <application/mynfs/requests/LseekRequest.h>
#include <application/mynfs/requests/UnlinkRequest.h>
#include <application//mynfs/requests/WriteRequest.h>
#include <application/mynfs/replies/ReadReply.h>
#include <iostream>
#include <fstream>
#include "../src/execution/handlers/OpenHandler.h"
#include "../src/execution/handlers/CloseHandler.h"
#include "../src/execution/handlers/ReadHandler.h"
#include "../src/execution/handlers/UnlinkHandler.h"
#include "../src/execution/handlers/LseekHandler.h"
#include "../src/execution/handlers/WriteHandler.h"

AccessManager setupAccessManager(const std::string &baseDir = "./test",
                                 const std::string &fsDir = "root",
                                 const std::string &hostsFile = "hosts.txt")
{
    std::fstream fileStream(baseDir + "/" + hostsFile, std::fstream::out | std::fstream::trunc);
    fileStream << "0.0.0.0" << std::endl;
    fileStream.close();
    return AccessManager(baseDir, fsDir, hostsFile);
}

TEST_CASE("Creating new file", "[OpenHandler]")
{
    std::string path = "testFile";
    DomainData replay;
    PlainError replayError;
    AccessManager accessManager = setupAccessManager();
    OpenHandler(DomainData(OpenRequest(path.data(), O_CREAT).serialize()),
                NetworkAddress(),
                replay,
                replayError,
                accessManager).handle(); //file will be created in server/bin
    CHECK(replayError.getErrorValue() == 0);
}

TEST_CASE("File to open does not exist", "[OpenHandler]")
{
    std::string path = "totek.txt";
    DomainData replay;
    PlainError replayError;
    AccessManager accessManager = setupAccessManager();
    OpenHandler(DomainData(OpenRequest(path.data(), O_RDONLY).serialize()),
                NetworkAddress(),
                replay,
                replayError,
                accessManager).handle();
    CHECK(replayError.getErrorValue() == ENOENT);

}

TEST_CASE("Close file", "[CloseHandler]")
{
    std::string path = "testFile";
    DomainData replay;
    PlainError replayError;
    AccessManager accessManager = setupAccessManager();
    int fd = open(path.data(), O_CREAT | O_RDONLY);
    CloseHandler(DomainData(CloseRequest(accessManager.generateAppDescriptor(IpAddress(), fd)).serialize()),
                 NetworkAddress(),
                 replay,
                 replayError,
                 accessManager).handle();
    CHECK(replayError.getErrorValue() == 0);
    close(fd);
    unlink(path.data());
}

TEST_CASE("Close unopened file", "[CloseHandler]")
{
    DomainData replay;
    PlainError replayError;
    AccessManager accessManager = setupAccessManager();
    int fd = 23;
    CloseHandler(DomainData(CloseRequest(accessManager.generateAppDescriptor(IpAddress(), fd)).serialize()),
                 NetworkAddress(),
                 replay,
                 replayError,
                 accessManager).handle();
    CHECK(replayError.getErrorValue() == EBADF);
}

TEST_CASE("Read file", "[ReadHandler]")
{
    std::byte buff[138];
    void *buf;
    buf = buff;
    std::string path = "testFile";
    DomainData replay(buf, 3);
    PlainError replayError;
    AccessManager accessManager = setupAccessManager();
    int fd = open(path.data(), O_CREAT | O_RDONLY);
    int count = 3;
    ReadHandler(DomainData(ReadRequest(accessManager.generateAppDescriptor(IpAddress(), fd), count).serialize()),
                NetworkAddress(),
                replay,
                replayError,
                accessManager).handle();
    ReadReply read(replay, replayError);
    auto b = read.getData().getData().size();
    for (int i = 0; i < b; i++)
    {
        std::cout << (char) read.getData().getData()[i];
    }
    CHECK(replayError.getErrorValue() == 0);
    close(fd);
    unlink(path.data());
}

TEST_CASE("Read unopened file", "[ReadHandler]")
{
    std::string path = "testFile";
    DomainData replay;
    PlainError replayError;
    AccessManager accessManager = setupAccessManager();
    int fd = 23;
    int count = 20;
    ReadHandler(DomainData(ReadRequest(accessManager.generateAppDescriptor(IpAddress(), fd), count).serialize()),
                NetworkAddress(),
                replay,
                replayError,
                accessManager).handle();
    CHECK(replayError.getErrorValue() == EBADF);
}

TEST_CASE("Use lseek", "[LseekHandler]")
{
    std::string path = "testFile";
    DomainData replay;
    PlainError replayError;
    AccessManager accessManager = setupAccessManager();
    int fd = open(path.data(), O_CREAT | O_RDONLY);
    int offset = 4;
    int whence = SEEK_SET;
    LseekHandler(
            DomainData(LseekRequest(accessManager.generateAppDescriptor(IpAddress(), fd), offset, whence).serialize()),
            NetworkAddress(),
            replay,
            replayError,
            accessManager).handle();
    CHECK(replayError.getErrorValue() == 0);
    close(fd);
    unlink(path.data());
}

TEST_CASE("Lseek on unopened file", "[LseekHandler]")
{
    DomainData replay;
    PlainError replayError;
    AccessManager accessManager = setupAccessManager();
    int fd = 10;
    int offset = 80;
    int whence = SEEK_END;
    LseekHandler(
            DomainData(LseekRequest(accessManager.generateAppDescriptor(IpAddress(), fd), offset, whence).serialize()),
            NetworkAddress(),
            replay,
            replayError,
            accessManager).handle();
    CHECK(replayError.getErrorValue() == EBADF);
}

TEST_CASE("Write on read only file", "[WriteHandler]")
{
    std::string path = "testFile";
    DomainData replay;
    PlainError replayError;
    AccessManager accessManager = setupAccessManager();
    int fd = open(path.data(), O_CREAT | O_RDONLY);
    std::vector<std::byte> data = {std::byte(0x1), std::byte(0x2), std::byte(0x3)};
    PlainData writeData(data);
    int count = 3;
    WriteHandler(DomainData(
            WriteRequest(accessManager.generateAppDescriptor(IpAddress(), fd), writeData.getData().data(),
                         writeData.getSize()).serialize()),
                 NetworkAddress(),
                 replay,
                 replayError,
                 accessManager).handle();
    CHECK(replayError.getErrorValue() == EBADF);
    close(fd);
    unlink(path.data());
}

TEST_CASE("Write on write only file", "[WriteHandler]")
{
    std::string path = "testFile";
    DomainData replay;
    PlainError replayError;
    AccessManager accessManager = setupAccessManager();
    int fd = open(path.data(), O_CREAT | O_WRONLY);
    std::vector<std::byte> data = {std::byte(0x41), std::byte(0x42), std::byte(0x43)};
    PlainData writeData(data);
    int count = 3;
    WriteHandler(DomainData(
            WriteRequest(accessManager.generateAppDescriptor(IpAddress(), fd), writeData.getData().data(),
                         writeData.getSize()).serialize()),
                 NetworkAddress(),
                 replay,
                 replayError,
                 accessManager).handle();
    CHECK(replayError.getErrorValue() == 0);
    close(fd);
    unlink(path.data());
}

TEST_CASE("Unlink on directory path", "[UnlinkHandler]")
{
    std::string path = ".";
    DomainData replay;
    PlainError replayError;
    AccessManager accessManager = setupAccessManager();
    UnlinkHandler(DomainData(UnlinkRequest(path.data()).serialize()),
                  NetworkAddress(),
                  replay,
                  replayError,
                  accessManager).handle();
    CHECK(replayError.getErrorValue() == EISDIR);
}

TEST_CASE("Unlink file", "[UnlinkHandler]")
{
    std::string path = "testFile";
    DomainData replay;
    PlainError replayError;
    AccessManager accessManager = setupAccessManager();
    int fd = open(path.data(), O_CREAT | O_WRONLY);
    UnlinkHandler(DomainData(UnlinkRequest(path.data()).serialize()),
                  NetworkAddress(),
                  replay,
                  replayError,
                  accessManager).handle();
    CHECK(replayError.getErrorValue() == 0);
    close(fd);
}
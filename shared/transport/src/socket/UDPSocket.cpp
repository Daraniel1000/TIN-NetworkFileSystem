#include <stdexcept>
#include <unistd.h>
#include "transport/socket/UDPSocket.h"
#include "addresses/AnyAddress.h"
#include "transport/read_interrupted_error.h"


UDPSocket::UDPSocket(Port port)
{
    auto protocol = 0; // protocol 0 means default
    this->socketDescriptor = socket(UDPSocket::FAMILY, UDPSocket::TYPE, protocol);
    if (this->socketDescriptor < 0)
        throw std::runtime_error("Can't create socket. Error " + std::to_string(errno) + ".");

    this->socketAddress = NetworkAddress(AnyAddress(), port);
    auto addressStruct = this->socketAddress.toStruct();

    if (bind(this->socketDescriptor, (struct sockaddr *) &addressStruct, sizeof(addressStruct)))
        throw std::runtime_error(
                "Can't bind socket to port " + std::to_string(this->socketAddress.getPort().toHostOrder()) +
                ". Error " + std::to_string(errno) + ".");

    int pipefd[2];
    if(pipe(pipefd))
        throw std::runtime_error(
                "Can't create signal pipe. Error " + std::to_string(errno) + ".");

    this->signalPipeRead = pipefd[0];
    this->signalPipeWrite = pipefd[1];
}

UDPSocket::~UDPSocket()
{
    close(this->socketDescriptor);
    close(this->signalPipeRead);
    close(this->signalPipeWrite);
}

void UDPSocket::send(NetworkAddress recipient, const PlainData &message) const
{
    const auto &messageData = message.getData();
    auto flags = 0; // no flags
    auto addressStruct = recipient.toStruct();

    auto sendBytes = sendto(this->socketDescriptor, messageData.data(), messageData.size(), flags,
                            (struct sockaddr *) &addressStruct,
                            sizeof(addressStruct));

    if (sendBytes < 0)
        throw std::runtime_error(
                "Sending message to " + recipient.toString() + " failed. Error " + std::to_string(errno) + ".");
}

PlainData UDPSocket::receive(NetworkAddress &source)
{
    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(this->socketDescriptor, &readSet);
    FD_SET(this->signalPipeRead, &readSet);

    if (select(this->socketDescriptor + 1, &readSet, nullptr, nullptr, nullptr) < 0)
        throw std::runtime_error(
                "Select failed. Error " + std::to_string(errno) + ".");

    if (FD_ISSET(this->signalPipeRead, &readSet))
    {
        std::byte dummyByte;
        read(this->signalPipeRead, &dummyByte, sizeof(dummyByte));
        throw read_interrupted_error();
    }

    sockaddr_in sourceAddress{};
    socklen_t sourceAddressLength = sizeof(sockaddr_in);
    auto flags = 0;

    int numBytes = recvfrom(this->socketDescriptor, this->readBuffer, UDPSocket::READ_BUFFER_SIZE, flags,
                            (struct sockaddr *)&sourceAddress, &sourceAddressLength);

    if(numBytes < 0)
        throw std::runtime_error(
                "Receiving failed. Error " + std::to_string(errno) + ".");

    source.setAddress(IpAddress(sourceAddress.sin_addr.s_addr));
    source.setPort(Port(sourceAddress.sin_port));
    return PlainData(this->readBuffer, numBytes);
}

void UDPSocket::signal() const
{
    std::byte dummyByte{0x1};
    write(this->signalPipeWrite, &dummyByte, sizeof(dummyByte));
}
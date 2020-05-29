#include <stdexcept>
#include <unistd.h>
#include <cstring>
#include <transport/timeout_error.h>
#include "transport/socket/UDPSocket.h"
#include "addresses/AnyAddress.h"
#include "transport/read_interrupted_error.h"

const int UDPSocket::MAX_DATA_SIZE = 65507;

UDPSocket::UDPSocket(Port port)
{
    // create socket
    auto protocol = 0; // protocol 0 means default
    this->socketDescriptor = socket(UDPSocket::FAMILY, UDPSocket::TYPE, protocol);
    if (this->socketDescriptor < 0)
        throw std::runtime_error("Can't create socket. " + std::string(strerror(errno)) + ".");

    this->socketAddress = NetworkAddress(AnyAddress(), port);
    auto addressStruct = this->socketAddress.toStruct();

    // bind to any address and given port
    if (bind(this->socketDescriptor, (struct sockaddr *) &addressStruct, sizeof(addressStruct)))
    {
        close(this->socketDescriptor); // close socket descriptor if failure
        throw std::runtime_error(
                "Can't bind socket to port " + std::to_string(this->socketAddress.getPort().toHostOrder()) +
                ". " + std::string(strerror(errno)) + ".");
    }

    sockaddr_in sin{};
    socklen_t len = sizeof(sin);
    if (getsockname(this->socketDescriptor, (struct sockaddr *) &sin, &len) == -1)
    {
        close(this->socketDescriptor); // close socket descriptor if failure
        throw std::runtime_error(
                "Can't get socket address. " + std::string(strerror(errno)) + ".");
    }

    this->socketAddress.setPort(Port(ntohs(sin.sin_port)));

    // create pipe for signaling
    int pipefd[2];
    if (pipe(pipefd))
    {
        close(this->socketDescriptor); // close socket descriptor if failure
        throw std::runtime_error(
                "Can't create signal pipe. " + std::string(strerror(errno)) + ".");
    }

    this->signalPipeRead = pipefd[0];
    this->signalPipeWrite = pipefd[1];
}

UDPSocket::~UDPSocket()
{
    // clear everything
    close(this->socketDescriptor);
    close(this->signalPipeRead);
    close(this->signalPipeWrite);
}

void UDPSocket::send(NetworkAddress recipient, const PlainData &message) const
{
    const auto &messageData = message.getData();
    auto flags = 0; // no flags
    auto addressStruct = recipient.toStruct(); // get address in struct form

    auto sendBytes = sendto(this->socketDescriptor, messageData.data(), messageData.size(), flags,
                            (struct sockaddr *) &addressStruct,
                            sizeof(addressStruct));

    if (sendBytes < 0)
        throw std::runtime_error(
                "Sending message to " + recipient.toString() + " failed. " + std::string(strerror(errno)) + ".");
}

PlainData UDPSocket::receive(NetworkAddress &source, int timeout) const
{
    // add descriptors to set
    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(this->socketDescriptor, &readSet);
    FD_SET(this->signalPipeRead, &readSet);

    timeval timeoutStruct{timeout, 0};
    timeval* timeoutStructPtr = nullptr;
    if(timeout >= 0)
        timeoutStructPtr = &timeoutStruct;

    auto nDescriptors = select(std::max(this->socketDescriptor, this->signalPipeRead) + 1,
                               &readSet,
                               nullptr,
                               nullptr,
                               timeoutStructPtr);

    if (nDescriptors < 0)
        throw std::runtime_error(
                "Select failed. " + std::string(strerror(errno)) + ".");
    if (nDescriptors == 0)
        throw timeout_error("Receive timed out");

    // check if signal woke us
    if (FD_ISSET(this->signalPipeRead, &readSet))
    {
        std::byte dummyByte;
        read(this->signalPipeRead, &dummyByte, sizeof(dummyByte)); // clear pipe
        throw read_interrupted_error();
    }

    // if it wasn't signal then it had to be socket
    sockaddr_in sourceAddress{};
    socklen_t sourceAddressLength = sizeof(sockaddr_in);
    auto flags = 0;
    std::byte readBuffer[MAX_DATA_SIZE];

    int numBytes = recvfrom(this->socketDescriptor, readBuffer, UDPSocket::MAX_DATA_SIZE, flags,
                            (struct sockaddr *) &sourceAddress, &sourceAddressLength);

    if (numBytes < 0)
        throw std::runtime_error(
                "Receiving failed. " + std::string(strerror(errno)) + ".");

    // set address of received message
    source.setAddress(IpAddress(ntohl(sourceAddress.sin_addr.s_addr)));
    source.setPort(Port(ntohs(sourceAddress.sin_port)));

    return PlainData(readBuffer, numBytes);
}

void UDPSocket::signal() const
{
    std::byte dummyByte{0x1};
    write(this->signalPipeWrite, &dummyByte, sizeof(dummyByte)); // write 1 byte to pipe
}

const NetworkAddress &UDPSocket::getAddress() const
{
    return this->socketAddress;
}

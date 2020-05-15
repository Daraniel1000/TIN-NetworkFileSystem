#include "application/mynfs/replies/OpenReply.h"

#include <utility>
#include <session/Converter.h>

OpenReply::OpenReply(int16_t descriptor, OpenReplyError error) : descriptor(descriptor), error(std::move(error)) {}

OpenReply::OpenReply(const DomainData& data, PlainError error) : error(error)
{
    auto expectedSize = sizeof(this->descriptor);
    if (data.getSize() != expectedSize)
        throw std::logic_error(
                "Bad message size. Expected " + std::to_string(expectedSize) + ", but got " +
                std::to_string(data.getSize()));

    //get descriptor
    this->descriptor = Converter::getInt16FromBytes(
            data.getNBytes(sizeof(this->descriptor)));
}

int16_t OpenReply::getDescriptor() const
{
    return this->descriptor;
}

const MyNFSError &OpenReply::getError() const
{
    return this->error;
}

DomainData OpenReply::getData() const
{
    // convert descriptor
    std::vector<std::byte> dataBytes = Converter::getBytesFromInt16(this->descriptor);

    return DomainData(dataBytes);
}

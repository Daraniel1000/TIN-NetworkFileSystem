#include <stdexcept>
#include <session/Converter.h>
#include <application/mynfs/bad_argument_error.h>
#include "application/mynfs/requests/CloseRequest.h"

const uint8_t CloseRequest::TYPE = 4;

CloseRequest::CloseRequest(int16_t descriptor) : descriptor(descriptor) {}

CloseRequest::CloseRequest(const DomainData &data)
{
    auto expectedSize = sizeof(this->descriptor);
    if (data.getSize() != expectedSize)
        throw bad_argument_error(1, 1,
                "Bad message size. Expected " + std::to_string(expectedSize) + ", but got " +
                std::to_string(data.getSize()));

    //get descriptor
    this->descriptor = Converter::getInt16FromBytes(
            data.getNBytes(sizeof(this->descriptor)));
}

int16_t CloseRequest::getDescriptor() const
{
    return this->descriptor;
}

uint8_t CloseRequest::getType() const
{
    return CloseRequest::TYPE;
}

DomainData CloseRequest::serialize() const
{
    // convert descriptor
    std::vector<std::byte> dataBytes = Converter::getBytesFromInt16(this->descriptor);

    return DomainData(dataBytes);
}

bool CloseRequest::operator==(const CloseRequest &rhs) const
{
    return descriptor == rhs.descriptor;
}

bool CloseRequest::operator!=(const CloseRequest &rhs) const
{
    return !(rhs == *this);
}

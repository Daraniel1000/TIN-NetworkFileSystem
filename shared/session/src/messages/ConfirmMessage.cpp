#include <stdexcept>
#include "session/messages/ConfirmMessage.h"

ConfirmMessage::ConfirmMessage(const PlainError& error) : error(error)
{}

ConfirmMessage::ConfirmMessage(const PlainData &data)
{
    Message::checkDataSize(data, sizeof(uint8_t) * 2);
    Message::checkDataType(data, ConfirmMessage::MESSAGE_TYPE);
    auto dataOffset = sizeof(ConfirmMessage::MESSAGE_TYPE);
    auto errorValue = ConfirmMessage::getUint8FromBytes(
            data.getNBytes(sizeof(uint8_t), dataOffset));
    this->error = PlainError(errorValue);
}

const PlainError &ConfirmMessage::getError() const
{
    return this->error;
}

PlainData ConfirmMessage::serialize() const
{
    std::vector<std::byte> msgBytes = ConfirmMessage::getBytesFromUint8(ConfirmMessage::MESSAGE_TYPE);
    auto errorBytes = ConfirmMessage::getBytesFromUint8(this->error.getErrorValue());
    msgBytes.insert(msgBytes.end(), errorBytes.begin(), errorBytes.end());
    return PlainData(msgBytes);
}

bool ConfirmMessage::operator==(const ConfirmMessage &rhs) const
{
    return error == rhs.error;
}

bool ConfirmMessage::operator!=(const ConfirmMessage &rhs) const
{
    return !(rhs == *this);
}

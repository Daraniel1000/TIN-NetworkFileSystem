#include "session/messages/DataMessage.h"

#include <utility>
#include <stdexcept>

DataMessage::DataMessage(int8_t type, DomainData data, PlainError error) : type(type), data(std::move(data)),
                                                                           error(error)
{}

DataMessage::DataMessage(const PlainData& data)
{
    auto expectedSize = sizeof(DataMessage::MESSAGE_TYPE) + sizeof(this->type) + sizeof(this->error.getErrorValue());
    if (data.getSize() < expectedSize)
        throw std::logic_error(
                "Bad message size. Expected at least" + std::to_string(expectedSize) + ", but got " +
                std::to_string(data.getSize()));

    Message::checkDataType(data, DataMessage::MESSAGE_TYPE);
    auto dataOffset = sizeof(DataMessage::MESSAGE_TYPE);

    auto errorValue = DataMessage::getUint8FromBytes(
            data.getNBytes(sizeof(uint8_t), dataOffset));
    this->error = PlainError(errorValue);
    dataOffset += sizeof(errorValue);

    auto reqType = DataMessage::getUint8FromBytes(
            data.getNBytes(sizeof(this->type), dataOffset));
    this->type = reqType;
    dataOffset += sizeof(reqType);

    auto dataSize = data.getSize() - dataOffset;
    this->data = DomainData(data.getNBytes(dataSize, dataOffset));
}

int8_t DataMessage::getType() const
{
    return this->type;
}

const PlainError& DataMessage::getError() const
{
    return this->error;
}

const DomainData& DataMessage::getData() const
{
    return this->data;
}

PlainData DataMessage::serialize() const
{
    std::vector<std::byte> msgBytes = DataMessage::getBytesFromUint8(DataMessage::MESSAGE_TYPE);

    auto errorBytes = DataMessage::getBytesFromUint8(this->error.getErrorValue());
    msgBytes.insert(msgBytes.end(), errorBytes.begin(), errorBytes.end());

    auto typeBytes = DataMessage::getBytesFromUint8(this->type);
    msgBytes.insert(msgBytes.end(), typeBytes.begin(), typeBytes.end());

    auto dataBytes = this->getData().getData();
    msgBytes.insert(msgBytes.end(), dataBytes.begin(), dataBytes.end());

    return PlainData(msgBytes);
}

bool DataMessage::operator==(const DataMessage &rhs) const
{
    return error == rhs.error &&
           type == rhs.type &&
           data == rhs.data;
}

bool DataMessage::operator!=(const DataMessage &rhs) const
{
    return !(rhs == *this);
}

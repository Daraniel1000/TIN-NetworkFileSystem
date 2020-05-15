#include <stdexcept>
#include "session/messages/Message.h"
#include "session/Converter.h"


void Message::checkDataSize(const PlainData &data, size_t expectedSize)
{
    if (data.getSize() != expectedSize)
        throw std::logic_error(
                "Bad message size. Expected " + std::to_string(expectedSize) + ", but got " +
                std::to_string(data.getSize()));
}

void Message::checkDataType(const PlainData& data, uint8_t expectedType)
{
    auto msgType = Converter::getUint8FromBytes(data.getNBytes(sizeof(uint8_t), 0));
    if (msgType != expectedType)
        throw std::logic_error(
                "Bad message type. Expected: " + std::to_string(expectedType) + ", but got " +
                std::to_string(msgType));
}
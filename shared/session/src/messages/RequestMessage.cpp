#include <session/Converter.h>
#include "session/messages/RequestMessage.h"

RequestMessage::RequestMessage(const PlainData& data)
{
    Message::checkDataSize(data, sizeof(RequestMessage::MESSAGE_TYPE));
    Message::checkDataType(data, RequestMessage::MESSAGE_TYPE);
}

PlainData RequestMessage::serialize() const
{
    // convert type only
    std::vector<std::byte> msgBytes = Converter::getBytesFromUint8(RequestMessage::MESSAGE_TYPE);
    return PlainData(msgBytes);
}
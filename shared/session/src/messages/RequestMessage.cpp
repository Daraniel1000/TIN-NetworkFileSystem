#include "session/messages/RequestMessage.h"

RequestMessage::RequestMessage(const PlainData& data)
{
    Message::checkDataSize(data, sizeof(RequestMessage::MESSAGE_TYPE));
    Message::checkDataType(data, RequestMessage::MESSAGE_TYPE);
}

PlainData RequestMessage::serialize() const
{
    std::vector<std::byte> msgBytes = RequestMessage::getBytesFromUint8(RequestMessage::MESSAGE_TYPE);
    return PlainData(msgBytes);
}
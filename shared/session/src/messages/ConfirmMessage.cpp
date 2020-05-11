#include "session/messages/ConfirmMessage.h"

ConfirmMessage::ConfirmMessage(int8_t error) : error(error) {}

ConfirmMessage::ConfirmMessage(PlainData data)
{

}

PlainData ConfirmMessage::serialize()
{
    return PlainData();
}
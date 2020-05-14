#include "session/messages/ConfirmMessage.h"

ConfirmMessage::ConfirmMessage(PlainError error) : error(error) {}

ConfirmMessage::ConfirmMessage(PlainData data)
{

}

PlainData ConfirmMessage::serialize()
{
    return PlainData();
}
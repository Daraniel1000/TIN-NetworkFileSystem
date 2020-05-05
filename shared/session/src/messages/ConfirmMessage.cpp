#include "session/messages/ConfirmMessage.h"

ConfirmMessage::ConfirmMessage()
= default;


ConfirmMessage::ConfirmMessage(PlainData data)
{

}

PlainData ConfirmMessage::serialize()
{
    return PlainData();
}
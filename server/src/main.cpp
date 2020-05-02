#include <iostream>
#include "messages/Message.h"
#include "socket/Socket.h"

int main()
{
    std::cout << "Hello World!" << Socket().getDataFromMessage(Message(5));
    return 0;
}
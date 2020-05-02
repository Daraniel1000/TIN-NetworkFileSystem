#include <iostream>
#include "messages/Message.hpp"
#include "socket/Socket.hpp"

int main()
{
    std::cout << "Hello World!" << Socket().getDataFromMessage(Message(5));
    return 0;
}
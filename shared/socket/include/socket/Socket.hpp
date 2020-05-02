
#ifndef MYNFS_SOCKET_HPP
#define MYNFS_SOCKET_HPP

#include "messages/Message.hpp"

class Socket
{
public:
    int getDataFromMessage(Message m);
};


#endif //MYNFS_SOCKET_HPP

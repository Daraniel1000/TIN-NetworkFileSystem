
#ifndef MYNFS_SOCKET_H
#define MYNFS_SOCKET_H

#include "messages/Message.h"

class Socket
{
public:
    int getDataFromMessage(Message m);
};


#endif //MYNFS_SOCKET_H

#include "../include/mynfslib.h"
#include "messages/Message.h"
#include "socket/Socket.h"

int mynfs_open() { return Socket().getDataFromMessage(Message(20)); }
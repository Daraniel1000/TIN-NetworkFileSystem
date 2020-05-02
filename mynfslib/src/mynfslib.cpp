#include "../include/mynfslib.hpp"
#include "messages/Message.hpp"
#include "socket/Socket.hpp"

int mynfs_open() { return Socket().getDataFromMessage(Message(20)); }

#ifndef MYNFS_MESSAGE_H
#define MYNFS_MESSAGE_H


class Message
{
    int data;
public:
    Message(int data) : data(data) {}
    int getData();
};


#endif //MYNFS_MESSAGE_H

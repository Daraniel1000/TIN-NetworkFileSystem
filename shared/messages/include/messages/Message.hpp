
#ifndef MYNFS_MESSAGE_HPP
#define MYNFS_MESSAGE_HPP


class Message
{
    int data;
public:
    Message(int data) : data(data) {}
    int getData();
};


#endif //MYNFS_MESSAGE_HPP

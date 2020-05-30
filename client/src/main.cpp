#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <vector>
#include <sstream>
#include <algorithm>
#include "mynfslib.h"

int16_t nfsopen()
{
    std::string host;
    std::string path;
    uint16_t oflag;
    std::string soflag;

    std::cout << "Host address:" << std::endl;
    std::getline(std::cin, host);
    std::cout << "Path to file:" << std::endl;
    std::getline(std::cin, path);
    std::cout << "Oflag:" << std::endl;
    std::cout << "Possible values: 0 O_RDONLY | 1 O_WRONLY | 2 O_RDWR | 1024 O_APPEND | 64 O_CREAT | 128 O_EXCL | 512 O_TRUNC" << std::endl;
    std::getline(std::cin, soflag);
    oflag = static_cast<uint16_t>(std::stoi(soflag));

    int16_t fd = mynfs_open(host.c_str(), path.c_str(), oflag);

    if(mynfs_error != 0 ) {
        std::cout << "Error occurred, error message: "<< mynfs_error_message << std::endl;
        return -1;
    }

    std::cout << "Success" << std::endl;
    std::cout << "Opened file descriptor: " << fd << std::endl;
    return fd;

}

int16_t nfsread()
{
    std::string host;
    int16_t fd;
    std::string sfd;
    int16_t count;
    std::string scount;
    char buf[4096];
    void *pBuf;
    pBuf = &buf[0];

    std::cout << "Host address:" << std::endl;
    std::getline(std::cin, host);
    std::cout << "File descriptor:" << std::endl;
    std::getline(std::cin, sfd);
    fd = static_cast<int16_t>(std::stoi(sfd));
    std::cout << "Bytes to read:" << std::endl;
    std::getline(std::cin, scount);
    count = static_cast<int16_t>(std::stoi(scount));

    int16_t size = mynfs_read(host.c_str(), fd, pBuf, count);

    if(mynfs_error != 0 ) {
        std::cout << "Error occurred, error message: "<< mynfs_error_message << std::endl;
        return -1;
    }

    std::cout << "Success" << std::endl;
    std::cout << size << " bytes read" << std::endl;

    int16_t i = 0;
    while(i < size)
    {
        std::cout << buf[i];
        if(i==100) std::cout << std::endl;
        i++;
    }

    return size;
}

int16_t nfswrite()
{
    std::string host;
    int16_t fd;
    std::string sfd;
    std::string buf;
    void *pBuf = &buf;
    int16_t count;

    std::cout << "Host address:" << std::endl;
    std::getline(std::cin, host);
    std::cout << "File descriptor:" << std::endl;
    std::getline(std::cin, sfd);
    fd = static_cast<int16_t>(std::stoi(sfd));
    std::cout << "Data to write:" << std::endl;
    std::getline(std::cin, buf);

    count = static_cast<int16_t>(buf.length());

    int16_t size = mynfs_write(host.c_str(), fd, pBuf, count);
    if(mynfs_error != 0 ) {
        std::cout << "Error occurred, error message: "<< mynfs_error_message << std::endl;
        return -1;
    }

    std::cout << "Success" << std::endl;
    std::cout << size << " bytes written" << std::endl;
    return size;
}

int32_t nfslseek()
{
    std::string host;
    std::string sfd;
    int16_t fd;
    std::string soffset;
    int32_t offset;
    std::string swhence;
    uint8_t whence;

    std::cout << "Host address:" << std::endl;
    std::getline(std::cin, host);
    std::cout << "File descriptor:" << std::endl;
    std::getline(std::cin, sfd);
    fd = static_cast<int16_t>(std::stoi(sfd));
    std::cout << "Offset:" << std::endl;
    std::getline(std::cin, sfd);
    offset = static_cast<int32_t>(std::stoi(soffset));
    std::cout << "Whence:" << std::endl;
    std::cout << "Possible values: 0 SEEK_SET | 1 SEEK_CUR | 2 SEEK_END" << std::endl;
    std::getline(std::cin, soffset);
    whence = static_cast<uint8_t>(std::stoi(swhence));

    offset = mynfs_lseek(host.c_str(), fd, offset, whence);

    if(mynfs_error != 0 ) {
        std::cout << "Error occurred, error message: "<< mynfs_error_message << std::endl;
        return -1;
    }

    std::cout << "Success" << std::endl;
    std::cout << "New offset: " << offset << std::endl;
    return offset;
}

int8_t nfsclose()
{
    std::string host;
    std::string sfd;
    int16_t fd;

    std::cout << "Host address:" << std::endl;
    std::getline(std::cin, host);
    std::cout << "File descriptor to close:" << std::endl;
    std::getline(std::cin, sfd);
    fd = static_cast<int16_t>(std::stoi(sfd));

    mynfs_close(host.c_str(), fd);

    if(mynfs_error != 0 ) {
        std::cout << "Error occurred, error message: "<< mynfs_error_message << std::endl;
        return -1;
    }

    std::cout << "Success" << std::endl;
    return 0;
}

int8_t nfsunlink()
{
    std::string host;
    std::string sfd;
    int16_t fd;

    std::cout << "Host address:" << std::endl;
    std::getline(std::cin, host);
    std::cout << "File descriptor to unlink:" << std::endl;
    std::getline(std::cin, sfd);
    fd = static_cast<int16_t>(std::stoi(sfd));

    mynfs_close(host.c_str(), fd);

    if(mynfs_error != 0 ) {
        std::cout << "Error occurred, error message: "<< mynfs_error_message << std::endl;
        return -1;
    }

    std::cout << "Success" << std::endl;
    return 0;
}

int main(int argc, char *argv[])
{
    std::string choice;
    bool exit = false;

    std::cout << "Welcome to MyNFS!\n";
    while(!exit)
    {
        std::cout << "Commands to run: open, read, write, lseek, close, unlink, exit\n";
        std::getline(std::cin, choice);
        if(choice =="open") nfsopen();

        else if(choice == "read") nfsread();

        else if(choice == "write") nfswrite();

        else if(choice == "lseek") nfslseek();

        else if(choice == "close") nfsclose();

        else if(choice == "unlink") nfsunlink();

        else if(choice == "exit") {exit = true; std::cout << "Goodbye!";}

        else std::cout << "Typo in command. Try again.\n";
    }
    return 0;
}
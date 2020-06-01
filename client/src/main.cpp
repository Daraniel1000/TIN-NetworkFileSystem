#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstddef>
#include <map>
#include "mynfslib.h"

int16_t chooseDescriptor(std::vector<int16_t> &openedDescriptors)
{
    std::cout << "Choose descriptor: ";
    for (auto d : openedDescriptors)
        std::cout << d << " ";;
    std::cout << std::endl;

    std::string fdStr;
    std::getline(std::cin, fdStr);
    auto fd = static_cast<int16_t>(std::stoi(fdStr));

    if (std::find(openedDescriptors.begin(), openedDescriptors.end(), fd) == openedDescriptors.end())
        return -1;

    return fd;
}

uint16_t orWord(uint16_t value, uint16_t word)
{
    return value | word;
}

int16_t nfsopen(std::string &host, std::vector<int16_t> &openedDescriptors)
{
    std::string path;
    uint16_t oflag = 0;
    std::string soflag;
    std::map<std::string, uint16_t>::iterator it;
    std::map<std::string, uint16_t> flags;

    flags["RDONLY"] = 0;
    flags["WRONLY"] = 1;
    flags["RDWR"] = 2;
    flags["APPEND"] = 1024;
    flags["CREAT"] = 64;
    flags["EXCL"] = 128;
    flags["TRUNC"] = 512;

    std::cout << "Path to file:" << std::endl;
    std::getline(std::cin, path);
    std::cout << "Oflag/s:" << std::endl;
    std::cout << "Possible values: RDONLY | WRONLY | RDWR | APPEND | CREAT | EXCL | TRUNC" << std::endl;
    std::cout << "In order to use more flags write them down with whitespaces between them." << std::endl;
    std::getline(std::cin, soflag);


    std::istringstream iss(soflag);
    std::string word;
    while (iss >> word)
    {
        it = flags.find(word);
        if (it != flags.end())
        {
            oflag = orWord(oflag, it->second);
        }
        else
        {
            std::cout << "Typo in oflags. Function aborted." << std::endl;
            return -1;
        }
    }

    int16_t fd = mynfs_open(host.c_str(), path.c_str(), oflag);

    if (mynfs_error != 0)
    {
        std::cout << "Error: " << mynfs_error_message << std::endl;
        return -1;
    }

    std::cout << "Success" << std::endl;
    std::cout << "Opened file descriptor: " << fd << std::endl;
    openedDescriptors.push_back(fd);
    return fd;
}

int16_t nfsread(std::string &host, std::vector<int16_t> &openedDescriptors)
{
    int16_t count;
    std::string scount;
    unsigned char buf[4096];
    void *pBuf;
    pBuf = &buf[0];

    if(openedDescriptors.empty())
    {
        std::cout << "No descriptors opened." << std::endl;
        return -1;
    }

    auto fd = chooseDescriptor(openedDescriptors);
    if (fd == -1)
    {
        std::cout << "Bad file descriptor " << fd << "." << std::endl;
        return -1;
    }

    std::cout << "Bytes to read:" << std::endl;
    std::getline(std::cin, scount);
    count = static_cast<int16_t>(std::stoi(scount));

    int16_t size = mynfs_read(host.c_str(), fd, pBuf, count);

    if (mynfs_error != 0)
    {
        std::cout << "Error: " << mynfs_error_message << std::endl;
        return -1;
    }

    std::cout << "Success" << std::endl;
    std::cout << size << " bytes read" << std::endl;

    int16_t i = 0;
    while (i < size)
    {
        std::cout << buf[i];
        if (i == 100) std::cout << std::endl;
        i++;
    }

    std::cout << std::endl;

    return size;
}

int16_t nfswrite(std::string &host, std::vector<int16_t> &openedDescriptors)
{
    std::string buf;

    int16_t count;

    if(openedDescriptors.empty())
    {
        std::cout << "No descriptors opened." << std::endl;
        return -1;
    }

    auto fd = chooseDescriptor(openedDescriptors);
    if (fd == -1)
    {
        std::cout << "Bad file descriptor " << fd << "." << std::endl;
        return -1;
    }

    std::cout << "Data to write:" << std::endl;
    std::getline(std::cin, buf);

    char *byteArray = buf.data();
    void *pBuf = byteArray;
    count = static_cast<int16_t>(buf.length());

    int16_t size = mynfs_write(host.c_str(), fd, pBuf, count);
    if (mynfs_error != 0)
    {
        std::cout << "Error: " << mynfs_error_message << std::endl;
        return -1;
    }

    std::cout << "Success" << std::endl;
    std::cout << size << " bytes written" << std::endl;
    return size;
}

int32_t nfslseek(std::string &host, std::vector<int16_t> &openedDescriptors)
{
    std::string soffset;
    int32_t offset;
    std::string swhence;
    uint8_t whence;
    std::map<std::string, uint8_t>::iterator it;
    std::map<std::string, uint8_t> flags;

    if(openedDescriptors.empty())
    {
        std::cout << "No descriptors opened." << std::endl;
        return -1;
    }

    auto fd = chooseDescriptor(openedDescriptors);
    if (fd == -1)
    {
        std::cout << "Bad file descriptor " << fd << "." << std::endl;
        return -1;
    }

    flags["SEEK_SET"] = 0;
    flags["SEEK_CUR"] = 1;
    flags["SEEK_END"] = 2;

    std::cout << "Offset:" << std::endl;
    std::getline(std::cin, soffset);
    offset = static_cast<int32_t>(std::stoi(soffset));
    std::cout << "Whence:" << std::endl;
    std::cout << "Possible values: SEEK_SET | SEEK_CUR | SEEK_END" << std::endl;
    std::getline(std::cin, swhence);

    it = flags.find(swhence);
    if (it != flags.end())
    {
        whence = it->second;
    }
    else
    {
        std::cout << "Typo in whence. Function aborted." << std::endl;
        return -1;
    }

    offset = mynfs_lseek(host.c_str(), fd, offset, whence);

    if (mynfs_error != 0)
    {
        std::cout << "Error: " << mynfs_error_message << std::endl;
        return -1;
    }

    std::cout << "Success" << std::endl;
    std::cout << "New offset: " << offset << std::endl;
    return offset;
}

int8_t nfsclose(std::string &host, std::vector<int16_t> &openedDescriptors)
{
    if(openedDescriptors.empty())
    {
        std::cout << "No descriptors opened." << std::endl;
        return -1;
    }

    auto fd = chooseDescriptor(openedDescriptors);
    if (fd == -1)
    {
        std::cout << "Bad file descriptor " << fd << "." << std::endl;
        return -1;
    }

    mynfs_close(host.c_str(), fd);

    if (mynfs_error != 0)
    {
        std::cout << "Error: " << mynfs_error_message << std::endl;
        return -1;
    }

    openedDescriptors.erase(std::remove(openedDescriptors.begin(), openedDescriptors.end(), fd),
                            openedDescriptors.end());

    std::cout << "Success" << std::endl;
    return 0;
}

int8_t nfsunlink(std::string &host)
{
    std::string path;
    std::cout << "Path to file:" << std::endl;
    std::getline(std::cin, path);


    mynfs_unlink(host.c_str(), path.c_str());

    if (mynfs_error != 0)
    {
        std::cout << "Error: " << mynfs_error_message << std::endl;
        return -1;
    }

    std::cout << "Success" << std::endl;
    return 0;
}

int main(int argc, char *argv[])
{
    std::string choice;
    std::string host;
    std::vector<int16_t> openedDescriptors;
    bool exit = false;
    std::cout << "Welcome to MyNFS!\n";
    std::cout << "Host address:" << std::endl;
    std::getline(std::cin, host);
    while (!exit)
    {
        std::cout << "Type command to run: open, read, write, lseek, close, unlink, exit\n";
        std::getline(std::cin, choice);
        if (choice == "open") nfsopen(host, openedDescriptors);

        else if (choice == "read") nfsread(host, openedDescriptors);

        else if (choice == "write") nfswrite(host, openedDescriptors);

        else if (choice == "lseek") nfslseek(host, openedDescriptors);

        else if (choice == "close") nfsclose(host, openedDescriptors);

        else if (choice == "unlink") nfsunlink(host);

        else if (choice == "exit")
        {
            exit = true;
<<<<<<< HEAD
            std::cout << "Goodbye!"<<std::endl;
=======
            std::cout << "Goodbye!\n";
>>>>>>> df5865873e7cc198a38d5be239114544a78ab255
        }

        else std::cout << "Typo in command. Try again.\n";
    }
    return 0;
}

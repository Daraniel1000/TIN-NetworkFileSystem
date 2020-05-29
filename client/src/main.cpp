#include <iostream>
#include <fcntl.h>
#include <cstring>
#include "mynfslib.h"

int16_t nfsopen()
{
    char host[50];
    char path[200];
    uint8_t oflag;

    std::cout << "Host address:" << std::endl;
    std::cin >> host;
    std::cout << "Path to file:" << std::endl;
    std::cin >> path;
    std::cout << "Oflag:" << std::endl;
    std::cin >> oflag;

    int16_t fd = mynfs_open(host, path, oflag);

    if(mynfs_error != 0 ) {
        std::cout << "Error occurred, error message: "<< mynfs_error_message << std::endl;
        return -1;
    }

    std::cout << "Success\nOpened file descriptor: " << fd << std::endl;
    return fd;

}

int16_t nfsread()
{
    char host[50];
    int16_t fd;
    void *buf[4096];
    int16_t count;

    std::cout << "Host address:" << std::endl;
    std::cin >> host;
    std::cout << "File descriptor:" << std::endl;
    std::cin >> fd;
    std::cout << "Bytes to read:" << std::endl;
    std::cin >> count;

    int16_t size = mynfs_read(host, fd, buf, count);

    if(mynfs_error != 0 ) {
        std::cout << "Error occurred, error message: "<< mynfs_error_message << std::endl;
        return -1;
    }

    std::cout << "Success" << std::endl;
    std::cout << size << " bytes read" << std::endl;
    std::cout << buf;
    return size;
}

int16_t nfswrite()
{
    char host[50];
    int16_t fd;
    void *buf[4096];
    int16_t count;

    std::cout << "Host address:" << std::endl;
    std::cin >> host;
    std::cout << "File descriptor:" << std::endl;
    std::cin >> fd;
    std::cout << "Bytes to save:" << std::endl;
    std::cin >> count;

    int16_t size = mynfs_write(host, fd, buf, count);

    if(mynfs_error != 0 ) {
        std::cout << "Error occurred, error message: "<< mynfs_error_message << std::endl;
        return -1;
    }

    std::cout << "Success" << std::endl;
    return size;
}

int32_t nfslseek()
{
    char host[50];
    int16_t fd;
    int32_t offset;
    int8_t whence;

    std::cout << "Host address:" << std::endl;
    std::cin >> host;
    std::cout << "File descriptor:" << std::endl;
    std::cin >> fd;
    std::cout << "Offset:" << std::endl;
    std::cin >> offset;
    std::cout << "Whence:" << std::endl;
    std::cin >> whence;

    offset = mynfs_lseek(host, fd, offset, whence);

    if(mynfs_error != 0 ) {
        std::cout << "Error occurred, error message: "<< mynfs_error_message << std::endl;
        return -1;
    }

    std::cout << "Success" << std::endl;
    return offset;
}

int8_t nfsclose()
{
    char host[50];
    int16_t fd;

    std::cout << "Host address:" << std::endl;
    std::cin >> host;
    std::cout << "File descriptor to close:" << std::endl;
    std::cin >> fd;

    mynfs_close(host, fd);

    if(mynfs_error != 0 ) {
        std::cout << "Error occurred, error message: "<< mynfs_error_message << std::endl;
        return -1;
    }

    std::cout << "Success" << std::endl;
    return 0;
}

int8_t nfsunlink()
{
    char host[50];
    int16_t fd;

    std::cout << "Host address:" << std::endl;
    std::cin >> host;
    std::cout << "File descriptor to unlink:" << std::endl;
    std::cin >> fd;

    mynfs_close(host, fd);

    if(mynfs_error != 0 ) {
        std::cout << "Error occurred, error message: "<< mynfs_error_message << std::endl;
        return -1;
    }

    std::cout << "Success" << std::endl;
    return 0;
}

int main(int argc, char *argv[])
{
    int choice;
    std::cout << "Welcome to MyNFS!\nChoose function to run:\n1. open\n2. read\n3. write\n4. lseek\n5. close\n6. unlink\n";
    std::cin >> choice;
        switch (choice) {
            case 1:
            {
                std::cout << "mynfs_open chosen" << std::endl;
                nfsopen();
                break;
            }
            case 2:
            {
                std::cout << "mynfs_read chosen" << std::endl;
                nfsread();
                break;
            }
            case 3:
            {
                std::cout << "mynfs_write chosen" << std::endl;
                nfswrite();
                break;
            }
            case 4:
            {
                std::cout << "mynfs_lseek chosen" << std::endl;
                nfslseek();
                break;
            }
            case 5:
            {
                std::cout << "mynfs_close chosen" << std::endl;
                nfsclose();
                break;
            }
            case 6:
            {
                std::cout << "mynfs_unlink chosen" << std::endl;
                nfsunlink();
                break;
            }
        }

}
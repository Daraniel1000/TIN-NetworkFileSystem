#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstddef>
#include <map>
#include <fstream>
#include "mynfslib.h"

int main(int argc, char *argv[])
{
    const int CHUNK_SIZE = 4096;

    std::string host;
    std::cout << "Welcome to MyNFS!\n";
    std::cout << "Server address (IP:PORT):" << std::endl;
    std::getline(std::cin, host);

    // open local file

    std::string filePath;
    std::cout << "Pass path to some big file (on your filesystem):" << std::endl;
    std::getline(std::cin, filePath);

    std::ifstream file(filePath, std::ios::binary);
    if(!file.is_open())
    {
        std::cout << "Can't open " + filePath << std::endl;
        return 1;
    }

    // open remote file

    std::cout << "Pass path to create file on server:" << std::endl;
    std::getline(std::cin, filePath);

    auto desc = mynfs_open(host.c_str(), filePath.c_str(), O_CREAT | O_RDWR);
    if(desc < 0)
    {
        std::cout << "Error " << mynfs_error << ": " << mynfs_error_message << std::endl;
        return 1;
    }

    // read local file and write to server

    char buf[CHUNK_SIZE];
    while(!file.eof())
    {
        file.read(buf, CHUNK_SIZE);
        auto writtenBytes = mynfs_write(host.c_str(), desc, buf, file.gcount());
        if(writtenBytes != file.gcount())
        {
            std::cout << "Error " << mynfs_error << ": " << mynfs_error_message << std::endl;
            return 1;
        }
    }

    std::cout << "Written file to the server." << std::endl;

    // open new local file

    std::cout << "Pass path to download file from server to:" << std::endl;
    std::getline(std::cin, filePath);

    std::ofstream fileOut(filePath, std::ios::out | std::ios::binary);
    if(!fileOut.is_open())
    {
        std::cout << "Can't open " + filePath << std::endl;
        return 1;
    }

    // lseek to beginning of remote file

    mynfs_lseek(host.c_str(), desc, 0, SEEK_SET);

    // read remote file and write to new local file

    int16_t readSize;
    while((readSize = mynfs_read(host.c_str(), desc, buf, CHUNK_SIZE)) != 0)
    {
        if(readSize == -1)
        {
            std::cout << "Error " << mynfs_error << ": " << mynfs_error_message << std::endl;
            return 1;
        }
        fileOut.write(buf, readSize);
    }

    std::cout << "Downloaded file from server." << std::endl;

    fileOut.close();

    std::cout << "Written file to " + filePath << std::endl;

    return 0;
}

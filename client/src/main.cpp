#include <iostream>
#include <fcntl.h>
#include "mynfslib.h"

int main()
{
    std::cout << "Hello World!" << " " << mynfs_open("locallhost:54321", "/path/to/file", O_RDONLY) << " " << mynfs_error;
    return 0;
}
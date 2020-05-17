#include <iostream>
#include <fcntl.h>
#include "mynfslib.h"

int main()
{
    std::cout << "Hello World!" << mynfs_open("localhost:54321", "/path/to/file", O_RDONLY);
    return 0;
}
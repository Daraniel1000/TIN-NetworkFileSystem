#ifndef MYNFS_READ_INTERRUPTED_ERROR_H
#define MYNFS_READ_INTERRUPTED_ERROR_H

#include <string>
#include <stdexcept>

class read_interrupted_error : public std::runtime_error
{
public:
    read_interrupted_error() : runtime_error("Read interrupted"){}
    explicit read_interrupted_error(const std::string& msg):runtime_error(msg.c_str()){}
};

#endif //MYNFS_READ_INTERRUPTED_ERROR_H

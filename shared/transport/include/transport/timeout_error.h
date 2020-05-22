#ifndef MYNFS_TIMEOUT_ERROR_H
#define MYNFS_TIMEOUT_ERROR_H

#include <string>
#include <stdexcept>

class timeout_error : public std::runtime_error
{
public:
    timeout_error() : runtime_error("Timed out"){}
    explicit timeout_error(const std::string& msg):runtime_error(msg.c_str()){}
};

#endif //MYNFS_TIMEOUT_ERROR_H

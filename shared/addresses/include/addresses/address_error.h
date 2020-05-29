#ifndef MYNFS_ADDRESS_ERROR_H
#define MYNFS_ADDRESS_ERROR_H

#include <string>
#include <stdexcept>
#include <unordered_map>

class address_error : public std::runtime_error
{
    int majorCode;
    int minorCode;
public:
    explicit address_error(int majorCode, int minorCode) : majorCode(majorCode), minorCode(minorCode),
                                                          runtime_error("Address error")
    {}

    explicit address_error(int majorCode, int minorCode, const std::string &msg) : majorCode(majorCode),
                                                                                  minorCode(minorCode),
                                                                                  runtime_error(msg.c_str())
    {}

    int getMajorCode() const { return majorCode; }
    int getMinorCode() const { return minorCode; }
};

#endif //MYNFS_ADDRESS_ERROR_H

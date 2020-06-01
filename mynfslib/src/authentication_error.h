#ifndef MYNFS_AUTHENTICATION_ERROR_H
#define MYNFS_AUTHENTICATION_ERROR_H

#include <string>
#include <stdexcept>
#include <unordered_map>

class authentication_error : public std::runtime_error
{
    int majorCode;
    int minorCode;
public:
    explicit authentication_error(int majorCode, int minorCode) : majorCode(majorCode), minorCode(minorCode),
                                                          runtime_error("Authentication error")
    {}

    explicit authentication_error(int majorCode, int minorCode, const std::string &msg) : majorCode(majorCode),
                                                                                  minorCode(minorCode),
                                                                                  runtime_error(msg.c_str())
    {}

    int getMajorCode() const { return majorCode; }
    int getMinorCode() const { return minorCode; }
};

#endif //MYNFS_AUTHENTICATION_ERROR_H

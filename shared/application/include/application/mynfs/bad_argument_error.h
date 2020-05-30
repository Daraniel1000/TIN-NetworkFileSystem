#ifndef MYNFS_BAD_ARGUMENT_ERROR_H
#define MYNFS_BAD_ARGUMENT_ERROR_H

#include <string>
#include <stdexcept>
#include <unordered_map>

class bad_argument_error : public std::runtime_error
{
    int majorCode;
    int minorCode;
public:
    explicit bad_argument_error(int majorCode, int minorCode) : majorCode(majorCode), minorCode(minorCode),
                                                          runtime_error("Bad argument error")
    {}

    explicit bad_argument_error(int majorCode, int minorCode, const std::string &msg) : majorCode(majorCode),
                                                                                  minorCode(minorCode),
                                                                                  runtime_error(msg.c_str())
    {}

    int getMajorCode() const { return majorCode; }
    int getMinorCode() const { return minorCode; }
};

#endif //MYNFS_BAD_ARGUMENT_ERROR_H

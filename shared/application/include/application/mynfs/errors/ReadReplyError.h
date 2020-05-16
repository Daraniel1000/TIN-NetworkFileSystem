#ifndef MYNFS_READREPLYERROR_H
#define MYNFS_READREPLYERROR_H


#include "MyNFSError.h"

class ReadReplyError : public MyNFSError
{
    const static std::unordered_map<int8_t, std::string> stringMap;
public:
    explicit ReadReplyError(int8_t errorValue = 0) {};
    explicit ReadReplyError(const PlainError& error) {};
    std::string toString() const override {};
};

#endif //MYNFS_READREPLYERROR_H

#ifndef MYNFS_LSEEKREPLYERROR_H
#define MYNFS_LSEEKREPLYERROR_H


#include "MyNFSError.h"

class LseekReplyError : public MyNFSError
{
    const static std::unordered_map<int8_t, std::string> stringMap;
public:
    explicit LseekReplyError(int8_t errorValue = 0);
    explicit LseekReplyError(const PlainError& error);
    std::string toString() const override;
};


#endif //MYNFS_LSEEKREPLYERROR_H

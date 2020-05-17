#ifndef MYNFS_CLOSEREPLYERROR_H
#define MYNFS_CLOSEREPLYERROR_H


#include "MyNFSError.h"

class CloseReplyError : public MyNFSError
{
    const static std::unordered_map<int8_t, std::string> stringMap;
public:
    explicit CloseReplyError(int8_t errorValue = 0);
    explicit CloseReplyError(const PlainError& error);
    std::string toString() const override;
};


#endif //MYNFS_CLOSEREPLYERROR_H

#ifndef MYNFS_WRITEREPLYERROR_H
#define MYNFS_WRITEREPLYERROR_H


#include "MyNFSError.h"

class WriteReplyError : public MyNFSError
{
    const static std::unordered_map<int8_t, std::string> stringMap;
public:
    explicit WriteReplyError(int8_t errorValue = 0);
    explicit WriteReplyError(const PlainError& error);
    std::string toString() const override;
};


#endif //MYNFS_WRITEREPLYERROR_H

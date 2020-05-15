#ifndef MYNFS_OPENREPLYERROR_H
#define MYNFS_OPENREPLYERROR_H


#include "MyNFSError.h"

class OpenReplyError : public MyNFSError
{
    const static std::unordered_map<int8_t, std::string> stringMap;
public:
    explicit OpenReplyError(int8_t errorValue = 0);
    explicit OpenReplyError(const PlainError& error);
    std::string toString() const override;
};


#endif //MYNFS_OPENREPLYERROR_H

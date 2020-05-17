#ifndef MYNFS_UNLINKREPLYERROR_H
#define MYNFS_UNLINKREPLYERROR_H


#include "MyNFSError.h"

class UnlinkReplyError : public MyNFSError
{
    const static std::unordered_map<int8_t, std::string> stringMap;
public:
    explicit UnlinkReplyError(int8_t errorValue = 0);
    explicit UnlinkReplyError(const PlainError& error);
    std::string toString() const override;
};


#endif //MYNFS_UNLINKREPLYERROR_H
